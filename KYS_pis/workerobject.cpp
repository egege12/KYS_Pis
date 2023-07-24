//
//
#include "workerobject.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>
#include <iterator>
#include <QtMath>
#define COM_INTERVAL 1000
#define CYCLETIMER_INTERVAL 500
#define LOG_SAVE_COUNTER 10
#define MIN_LOG_DEL_SIZE 104857600
#define MAX_LOG_SIZE 1073741824





workerObject::workerObject(QObject *parent, endPointsClass *endPoints)
{
    this->endPoints = endPoints;
    this->failCounterLifeSign=0;
    this->failGPSCounter=0;
    this->GPSLatitude =0.0;
    this->GPSLongtitude=0.0;
    this->processBlockedConnection=false;
    this->processBlockedFileLines=false;
    this->processBlockedService=false;
}

workerObject::~workerObject()
{
    saveLogs();
}

bool workerObject::checkConnection()
{
QNetworkAccessManager manager;
QNetworkRequest request(QUrl("https://www.google.com"));

QNetworkReply *reply = manager.get(request);
QEventLoop loop1;

connect(reply,&QNetworkReply::finished,&loop1,&QEventLoop::quit,Qt::AutoConnection);
loop1.exec();

if (reply->error() == QNetworkReply::NoError) {
    // İnternet bağlantısı mevcut
        if(!this->endPoints->stateNetwork()){
            this->endPoints->setErrCode("-checkConnection- İnternet bağlantısı sağlandı");
        }
        this->endPoints->setStateNetwork(true);
        delete reply;
        return true;
} else {
    // İnternet bağlantısı yok veya erişim hatası
        if(this->endPoints->stateNetwork()){
            this->endPoints->setErrCode("-checkConnection- İnternet bağlantısı yok");
        }
        this->endPoints->setStateNetwork(false);
        delete reply;
        return false;
}

}

bool workerObject::checkService()
{

QNetworkAccessManager manager;
QString url("https://kaktusmobile.kayseriulasim.com.tr/api/LineStops");
QNetworkRequest request(QUrl(QString("%1?lineId=%2&direction=1").arg(url).arg(0)));

QNetworkReply* reply = manager.get(request);
QEventLoop loop1;
QObject::connect(reply, &QNetworkReply::finished, &loop1, &QEventLoop::quit);
bool serviceStat;
loop1.exec();

    if (reply->error() == QNetworkReply::NoError) {
        this->endPoints->setErrCode("-checkService- Servis aktif.");
        serviceStat = true;
    } else {
        this->endPoints->setErrCode("-checkService- Servis yanıt vermiyor.");
        serviceStat = false;
    }
    reply->deleteLater();
    return serviceStat;
}

void workerObject::checkLifeSign(unsigned int oldLifeSign, unsigned int newLifeSign)
{
    if(oldLifeSign !=newLifeSign){
        this->failCounterLifeSign = 0;
    }else{
        this->failCounterLifeSign++;
    }

}

bool workerObject::checkGPS()
{

    if(!this->endPoints->iiCom.GPSOk){
        qDebug()<<"GPS STATUS :"<<this->endPoints->iiCom.GPSOk;
        return false;
    }else{
        if(this->endPoints->iiCom.GPSLatitude != this->GPSLatitude){
            this->failGPSCounter=0;
        }else if(this->endPoints->iiCom.GPSLongtitude != this->GPSLongtitude){
            this->failGPSCounter=0;
        }else{
            ++this->failGPSCounter;
        }
        if((failGPSCounter>20) && this->endPoints->iiCom.VehicleSpeed>5){
            return false;
        }else{
            return true;
        }
    }
}

bool workerObject::checkFolderStations()
{
    bool folderStationsOK;

    {
        QString path = "C:/appKYS_Pis/PISStations";
        QDir directory(path);

        if (directory.exists()) {
           folderStationsOK = true;
        }else {
           directory.mkpath(path);
           if (directory.exists()){
               folderStationsOK = true;
               this->endPoints->setErrCode("PISStations mevcut değil, oluşturuldu");
           }else{
               folderStationsOK = false;
               this->endPoints->setErrCode("PISStations mevcut değil ve oluşturulamadı");
           }

        }
    }
return folderStationsOK ;
}

bool workerObject::checkFileLines()
{
bool lineCsvOK;
{       //Is lineCsvOK ?
        QString filePath = "C:/appKYS_Pis/PISStations/dataLines.csv"; // Kontrol edilecek dosyanın yolu

        QFile file(filePath);
        if (file.exists()) {
           lineCsvOK = true;
        } else {
           lineCsvOK = false;
        }
}
return lineCsvOK;
}

bool workerObject::checkFileJson()
{
bool jsonFileOK = true;
      //Is lineCsvOK ?
        QString filePath = "C:/appKYS_Pis/PISStations/dataStations.json"; // Kontrol edilecek dosyanın yolu

        QFile file(filePath);
        if (file.exists()) {
           if (!file.open(QIODevice::ReadOnly)) {
               this->endPoints->setErrCode("-checkFileJson- JSON dosyası açılamadı");
               jsonFileOK = false;
           }
           QByteArray fileData = file.readAll();
           file.close();

           QJsonDocument fileDoc = QJsonDocument::fromJson(fileData);
           if (!fileDoc.isArray()) {
               this->endPoints->setErrCode("-checkFileJson- JSON verisi geçersiz");
                   file.remove(filePath);
                   jsonFileOK = false;
           }

           QJsonArray existingDataStations = fileDoc.array();
           bool lineIdNotFoundExt = false;
           for(const QString& LineId : this->lines){
               bool lineIdFoundInn = false;
               for (int i = 0; i < existingDataStations.size(); ++i) {
                    QJsonObject existingLineObj = existingDataStations.at(i).toObject();
                    if (existingLineObj.contains("lineId")) {
                        if (existingLineObj["lineId"].toString() == LineId){
                            lineIdFoundInn = true;
                        }
                    }else{
                        jsonFileOK = false;
                    }
               }
               if(!lineIdFoundInn){
                    lineIdNotFoundExt = true;
               }
           }
           if(lineIdNotFoundExt){
               jsonFileOK = false;
           }
        } else {
           jsonFileOK = false;
        }
        return jsonFileOK;
}

void workerObject::readVideoFolder()
{
        this->endPoints->videoList.clear();
        QString csvFilePath ="C:/appKYS_Pis/PISVideos/dataCommercial.csv";
        QString folderPath  = "C:/appKYS_Pis/PISVideos";
        QFile csvFile(csvFilePath);
        if (!csvFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug() << "CSV dosyası açılamadı!";
           return;
        }

        QTextStream in(&csvFile);
        bool isFirstLine = true;
        while (!in.atEnd()) {
           QString line = in.readLine();
           if (isFirstLine) {
               isFirstLine = false;
               continue; // Başlık satırını pas geç
           }
           QStringList data = line.split(",");
           if (data.size() >= 2) {
               endPointsClass::videos video;
               video.id = data[0]+".mp4";
               video.description = data[1];
               this->endPoints->videoList.append(video);
           }
        }
        csvFile.close();

        QDir videoFolder(folderPath);
        QStringList folderVideoNames = videoFolder.entryList(QStringList() << "*.mp4", QDir::Files);
        for (const QString& videoName : folderVideoNames) {
           bool found = false;
           for (const endPointsClass::videos& video : this->endPoints->videoList) {
               if (video.id == videoName) {
                    found = true;
                    break;
               }
           }

           if (!found) {
               qDebug() << "Uyarı: CSV dosyasında olmayan video: " << videoName;
               this->endPoints->setErrCode("Klasörde olup veritabanında olmayan video: " + videoName);
           }
        }

        for (const endPointsClass::videos& video : this->endPoints->videoList) {
           QString videoFilePath = folderPath + "/" + video.id;
           if (!videoFolder.exists(video.id)) {
               qDebug() << "Uyarı: Klasörde olmayan video: " << video.id;
               this->endPoints->setErrCode("Veritabanında olup klasörde olmayan video: " + video.id);
           } else {
               this->endPoints->videoList.append(video);
           }
        }
        emit endPoints->videoFolderUpdated();
}

void workerObject::enableCycleCheckUpdate(bool cycleCheckUpdate)
{
        this->cycleCheckUpdate=cycleCheckUpdate;
}

void workerObject::enableCycleCheckRead(bool cycleCheckRead)
{
        this->cycleCheckRead=cycleCheckRead;
}

bool workerObject::checkFolderVideo()
{
    bool folderVideosOK;

    {
        QString path = "C:/appKYS_Pis/PISVideos";
        QDir directory(path);

        if (directory.exists()) {
           folderVideosOK = true;
        }else {
           directory.mkpath(path);
           if (directory.exists()){
               folderVideosOK = true;
               this->endPoints->setErrCode("PISVideos klasörü mevcut değildi, oluşturuldu");
           }else{
               folderVideosOK = false;
               this->endPoints->setErrCode("PISVideos klasörü mevcut değil ve oluşturulamadı");
           }

        }
    }
return folderVideosOK ;
}

bool workerObject::checkFolderAudioForLines()
{
QList<bool> foldersOk; // Added further needs, It holds folder status
unsigned i =0;
if(!lines.empty()){
        foreach(QString line , lines){
           {

               QString path = "C:/appKYS_Pis/"+line.trimmed()+"";
               QDir directory(path);

               if (directory.exists()) {
                   foldersOk[i] = true;
               }else {
                   directory.mkpath(path);
                   if (directory.exists()){
                       foldersOk[i] = true;
                       this->endPoints->setErrCode(line.trimmed()+" hattı ses klasörü mevcut değil, oluşturuldu");
                   }else{
                       foldersOk[i] = false;
                       this->endPoints->setErrCode(line.trimmed()+" hattı ses klasörü mevcut değil, oluşturulamadı");
                   }
               }
               if(foldersOk[i]){
                   QString path2 = "C:/appKYS_Pis/"+line.trimmed()+"/1";
                   QDir directory2(path2);
                   directory2.mkpath(path2);
                   QString path3 = "C:/appKYS_Pis/"+line.trimmed()+"/2";
                   QDir directory3(path3);
                   directory3.mkpath(path3);
               }
               ++i;
           }
        }
        return true;
}else
    return false;
}

bool workerObject::checkFolderSpecialAnouncement()
{
 bool folderSpecialAnounceOK;
{
    QString path = "C:/appKYS_Pis/PISSpecialAnounce";
    QDir directory(path);

    if (directory.exists()) {
           folderSpecialAnounceOK = true;
    }else {
           directory.mkpath(path);
           if (directory.exists()){
               folderSpecialAnounceOK = true;
               this->endPoints->setErrCode("PISSpecialAnounce klasörü mevcut değil, oluşturuldu");
           }else{
               folderSpecialAnounceOK = false;
               this->endPoints->setErrCode("PISSpecialAnounce klasörü mevcut değil ve oluşturulamadı");
           }
    }
}
return  folderSpecialAnounceOK;
}

void workerObject::compareAndCopyFile(const QString &sourcePath, const QString &destinationPath)
{
QFile sourceFile(sourcePath);
QFile destinationFile(destinationPath);
QDir backupDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups");
backupDir.mkpath(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups");

if (sourceFile.open(QIODevice::ReadOnly | QIODevice::Text) &&
    destinationFile.open(QIODevice::ReadWrite | QIODevice::Text))
{
    QTextStream sourceStream(&sourceFile);
    QTextStream destinationStream(&destinationFile);

    QString sourceContent = sourceStream.readAll();
    QString destinationContent = destinationStream.readAll();

    if (sourceContent != destinationContent)
    {
           destinationFile.close();

           if (destinationFile.open(QIODevice::WriteOnly | QIODevice::Text))
           {
               QTextStream writeStream(&destinationFile);
               writeStream << sourceContent;
               qDebug() << "File has been successfully copied to the destination.";
           }
           else
           {
               qDebug() << "Error opening the destination file for writing.";
           }
    }
    else
    {
           qDebug() << "The file at the destination are the same. No action taken.";
    }

    sourceFile.close();
    destinationFile.close();
}
else
{
    qDebug() << "Error opening the files. Please check the file paths.";
}
}

void workerObject::saveLogs()
{

    {
        QString path = "C:/appKYS_Pis/PISLog";
        QDir directory(path);

        if (directory.exists()) {
               //qDebug()<<"PISLog klasörü var";
        } else {
           directory.mkpath(path);
           this->endPoints->setErrCode("PISLog mevcut değil, oluşturuldu");
        }
    }

    QString path= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir directory(path+"/appKYS_Pis/Log");
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("Dyyyy_MM_dd");


    if(directory.exists()){
        // do nothing
    }else{
        directory.mkpath(path+"/appKYS_Pis/Log");
        this->endPoints->setErrCode("log dosyası bulunamadı ve oluşturuldu.");
    }


    QFile logFile1(path+"/appKYS_Pis/Log/"+formattedDateTime+"_logs.PISLog");
    if(logFile1.exists()){
        if (!logFile1.open(QIODevice::Append)){
            this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
        }else{

            QTextStream out1(&logFile1);
             foreach(QString logLine1 , this->endPoints->errList){
                 if(!logLine1.isEmpty()){
                    out1<<logLine1<<Qt::endl;
                 }
            }
            logFile1.close();
        }
    }else{
        if (!logFile1.open(QIODevice::WriteOnly| QIODevice::Truncate )){
             this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
        }else{
            QTextStream out1(&logFile1);
             foreach(QString logLine1 , this->endPoints->errList){
                if(!logLine1.isEmpty()){
                    out1<<logLine1<<Qt::endl;
                }
            }
            logFile1.close();
        }
    }

    QFile logFile2("C:/appKYS_Pis/PISLog/"+formattedDateTime+"_logs.PISLog");
    if(logFile2.exists()){
        if (!logFile2.open(QIODevice::Append  )){
            this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
        }else{
            qint64 fileSize = logFile2.size();
            logFile2.seek(fileSize);
            QTextStream out2(&logFile2);
            foreach(QString logLine2 , this->endPoints->errList){
               out2<<logLine2<<Qt::endl;
            }
            logFile2.close();
        }
    }else{
        if (!logFile2.open(QIODevice::WriteOnly| QIODevice::Truncate )){
             this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
        }else{
            QTextStream out2(&logFile2);
            foreach(QString logLine2 , this->endPoints->errList){
               out2<<logLine2<<Qt::endl;
            }
            logFile2.close();
        }
    }
    this->endPoints->errList.clear();

}

void workerObject::deleteOldestFiles(QString folderPath)
{
    QDir folder(folderPath);
    qint64 totalSize = 0;

    QFileInfoList fileInfoList = folder.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Time);

    for (const QFileInfo& fileInfo : fileInfoList) {
        totalSize += fileInfo.size();
    }

    this->endPoints->setErrCode("Klasör boyutu:" + QString::number(totalSize / (1024 * 1024)) + "MB");

        if (totalSize > MAX_LOG_SIZE) {
    this->endPoints->setErrCode( "Klasör boyutu MAX_LOG_SIZE'ı geçti!");
    qint64 sizeToDelete = totalSize - MAX_LOG_SIZE;
    int deletedFilesCount = 0;

    for (const QFileInfo& fileInfo : fileInfoList) {
        if (fileInfo.isFile() && fileInfo.size() > MIN_LOG_DEL_SIZE) {
            this->endPoints->setErrCode("Dosya siliniyor:" + fileInfo.fileName());
            if (QFile::remove(fileInfo.filePath())) {
               totalSize -= fileInfo.size();
               deletedFilesCount++;
              this->endPoints->setErrCode("Dosya başarıyla silindi.");
            } else {
              this->endPoints->setErrCode("Dosya silinirken bir hata oluştu.");
            }
            // Klasör boyutu hedefi aştıysa döngüyü sonlandır
            if (totalSize <= MAX_LOG_SIZE) {
               break;
            }
        }
    }

    this->endPoints->setErrCode(QString::number(deletedFilesCount) + "dosya silindi.");
    }
}
void workerObject::readStations()
{
    this->endPoints->setFolderStructureOK(checkFolderAudioForLines()&&checkFolderStations()&&checkFolderVideo()&&checkFileLines());
    bool stationsRead = false;

    bool processBlockedFileLines = !readLineLIST(true);

    if(checkFileJson()){
        stationsRead = readJSON(false);
    }else{
        if(!processBlockedFileLines){
            if(!((processBlockedService = !(checkConnection())) || (processBlockedConnection= !(checkService())))){
               sendHttpReq();
               stationsRead = readJSON(false);
           }else{
               stationsRead = readJSON(true);
               QString destinationPath = "C:/appKYS_Pis/PISStations/dataStations.json";
               QString sourcePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataStations.json";
               compareAndCopyFile(sourcePath, destinationPath);
           }
        }else{
           stationsRead = readJSON(true);
        }
    }
    this->enableCycleCheckRead(!stationsRead);
    if (stationsRead){
        this->endPoints->setErrCode("-readStations- istasyonlar okundu.");
    }else{
        this->endPoints->setErrCode("-readStations- istasyonlar okunamadı.");
    }

    this->endPoints->setDataImported(stationsRead);

}


void workerObject::startObject()
{
    timer1 = new QTimer(this);
    timer1->setInterval(COM_INTERVAL);
    QObject::connect(timer1,&QTimer::timeout,this,&workerObject::rwComApp,Qt::AutoConnection);
    timer1->start();
    timer2 = new QTimer(this);
    timer2->setInterval(CYCLETIMER_INTERVAL);
    QObject::connect(timer2,&QTimer::timeout,this,&workerObject::cycleCall,Qt::AutoConnection);
    timer2->start();


    QObject::connect(this->endPoints,&endPointsClass::updateStationsChanged,this,&workerObject::updateList,Qt::AutoConnection);
    QObject::connect(this->endPoints,&endPointsClass::lineSelectedChanged,this,&workerObject::handleLineSelection,Qt::AutoConnection);
    QObject::connect(this->endPoints,&endPointsClass::StationConfirmedChanged,this,&workerObject::confirmLineSelection,Qt::AutoConnection);
    readStations();
    readVideoFolder();
}

void workerObject::stopObject()
{
    QObject::disconnect(timer1,&QTimer::timeout,this,&workerObject::rwComApp);
    QObject::disconnect(timer2,&QTimer::timeout,this,&workerObject::cycleCall);
    timer1->stop();
    timer2->stop();
    delete timer1;
    delete timer2;
    //Nothing here
    QObject::disconnect(this->endPoints,&endPointsClass::updateStationsChanged,this,&workerObject::updateList);
}
void workerObject::saveDataStations(const QJsonArray& dataStations)
{
    // Dosya yolu
    QString filePath = "C:/appKYS_Pis/PISStations/dataStations.json";

    // Dosya kontrolü
    QFile file(filePath);
    bool fileExists = file.exists();

    // Dosyayı aç veya oluştur
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Dosya açılamadı!";
        return;
    }

    // JSON verisini yaz
    QJsonDocument doc(dataStations);
    QByteArray jsonData = doc.toJson();

    // Dosyayı boşalt ve veriyi yaz
    file.resize(0);
    file.write(jsonData);
    file.close();

    if (fileExists) {
        qDebug() << "Dosya güncellendi!";
    } else {
        qDebug() << "Dosya oluşturuldu!";
    }
}
void workerObject::sendHttpReq()
{
    QString apiUrl = "https://kaktusmobile.kayseriulasim.com.tr/api/LineStops";


    for (const QString& lineId : lines) {

        QString query1 = QString("%1?lineId=%2&direction=1").arg(apiUrl).arg(lineId);
        QNetworkAccessManager manager;
        QNetworkReply *reply1 = manager.get(QNetworkRequest(QUrl(query1)));

        QEventLoop loop1;
        QObject::connect(reply1, &QNetworkReply::finished, &loop1, &QEventLoop::quit);

        loop1.exec();
        QString query2 = QString("%1?lineId=%2&direction=2").arg(apiUrl).arg(lineId);
        QNetworkReply *reply2 = manager.get(QNetworkRequest(QUrl(query2)));

        QEventLoop loop2;
        QObject::connect(reply2, &QNetworkReply::finished, &loop2, &QEventLoop::quit);

        loop2.exec();

        if ((reply1->error() == QNetworkReply::NoError) && (reply2->error() == QNetworkReply::NoError)) {
           QByteArray responseData1 = reply1->readAll();
           QJsonParseError jsonParseError1;
           QJsonDocument json1 = QJsonDocument::fromJson(responseData1, &jsonParseError1);
           QByteArray responseData2 = reply2->readAll();
           QJsonParseError jsonParseError2;
           QJsonDocument json2 = QJsonDocument::fromJson(responseData2, &jsonParseError2);
           if ((jsonParseError1.error == QJsonParseError::NoError && !json1.isNull() && !json1.isEmpty()) && (jsonParseError2.error == QJsonParseError::NoError && !json2.isNull() && !json2.isEmpty())) {
               QJsonObject lineObj;
               lineObj.insert("lineId", lineId);
               if (json1.isEmpty()) {
                   qDebug() << "Yön bulunamadı!";
                   lineObj.insert("direction1", QJsonArray());
               } else {
                   lineObj.insert("direction1", json1.array());
               }
               if (json2.isEmpty()) {
                   qDebug() << "Yön bulunamadı!";
                   lineObj.insert("direction2", QJsonArray());
               } else {
                   lineObj.insert("direction2", json2.array());
               }

               QFile file("C:/appKYS_Pis/PISStations/dataStations.json");
               if (file.exists()) {
                   if (!file.open(QIODevice::ReadOnly)) {
                       qDebug() << "Dosya açılamadı!";
                       return;
                   }
                   QByteArray fileData = file.readAll();
                   file.close();

                   QJsonDocument fileDoc = QJsonDocument::fromJson(fileData);
                   if (!fileDoc.isArray()) {
                       qDebug() << "Geçersiz JSON verisi!";
                           return;
                   }

                   QJsonArray existingDataStations = fileDoc.array();
                   bool lineIdFound = false;
                   for (int i = 0; i < existingDataStations.size(); ++i) {
                       QJsonObject existingLineObj = existingDataStations.at(i).toObject();
                       if (existingLineObj.contains("lineId") && existingLineObj["lineId"].toString() == lineId) {
                           existingDataStations.replace(i, lineObj);
                           lineIdFound = true;
                           break;
                       }
                   }
                   for (int i = 0; i < existingDataStations.size(); ++i) {
                       QJsonObject existingLineObj = existingDataStations.at(i).toObject();
                       if(existingLineObj.contains("lineId")){
                           bool lineNotContains = true;
                           for(const QString& line : this->lines){
                                if(line == (existingLineObj["lineId"].toString())){
                                   lineNotContains = false;
                                }
                           }
                           if (lineNotContains){
                                qDebug() << "REMOVE";
                                existingDataStations.removeAt(i);
                           }
                       }
                   }

                   if (!lineIdFound) {
                       existingDataStations.append(lineObj);
                   }
                   saveDataStations(existingDataStations);
               } else {
                   QJsonArray newDataStations;
                   newDataStations.append(lineObj);
                   saveDataStations(newDataStations);
               }
           }
        }

        reply1->deleteLater();
        reply2->deleteLater();
    }
    QString sourcePath = "C:/appKYS_Pis/PISStations/dataStations.json";
    QString destinationPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataStations.json";
    compareAndCopyFile(sourcePath, destinationPath);
}

bool workerObject::readJSON(bool useBackup)
{
    bool statJson = true;
    QString filePath = useBackup? QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataStations.json":"C:/appKYS_Pis/PISStations/dataStations.json"; // Kontrol edilecek dosyanın yolu
    QFile file(filePath);
    if(useBackup){
        this->endPoints->setErrCode("-readJSON- Yedek veri kullanılacak.");
    }
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) {
           this->endPoints->setErrCode("-readJSON- JSON dosyası açılamadı");
           return false;
        }
        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument fileDoc = QJsonDocument::fromJson(fileData);
        if (!fileDoc.isArray()) {
           this->endPoints->setErrCode("-readJSON- JSON verisi geçersiz");
               return false;
        }

        QJsonArray existingDataStations = fileDoc.array();
        bool lineIdFound = false;
        for (int i = 0; i < existingDataStations.size(); ++i) {
           QJsonObject existingLineObj = existingDataStations.at(i).toObject();
           QString ID = existingLineObj["lineId"].toString();


           if(!existingLineObj["direction1"].isArray() || existingLineObj["direction1"].isNull()){
               qDebug()<<"direction1 array değil";
           }else{
               QJsonArray direction1 = existingLineObj["direction1"].toArray();
                QList<endPointsClass::station*> listStations;
               for(int k =0; k<direction1.size();++k){
                   QJsonObject station = direction1.at(k).toObject();
                   if(station.contains("id") && station.contains("latitude") && station.contains("longitude") && station.contains("name")){
                       endPointsClass::station* newStation = new  endPointsClass::station;
                       newStation->id = QString::number(station["id"].toInt());
                       newStation->latitude = QString::number(station["latitude"].toDouble());
                       newStation->longitude = QString::number(station["longitude"].toDouble());
                       newStation->name = station["name"].toString();
                       //qDebug()<<newStation->id<<" "<<newStation->name<<" "<<newStation->latitude << " "<< newStation->longitude;
                       listStations.append(newStation);
                   }else{
                       endPoints->setErrCode("-readJSON-"+ID+"hat numarası yön 1 verisi için ID,enlem,boylam,isim alt üyeleri eksik, JSON okunamıyor. ");
                       statJson = false;
                   }
               }

                if(listStations.size() == direction1.size()){
                   if(listStations.size()>0){
                       endPoints->addItemStations(ID,"1",listStations);
                   }
                }else{
                     qDebug()<<"-readJSON-"<<ID<<"hat numarası yön 1 verisi eksik okundu. ";
                     endPoints->setErrCode("-readJSON-"+ID+"hat numarası yön 1 verisi eksik okundu. ");
                     return false;
                }
           }

           if(!existingLineObj["direction2"].isArray() || existingLineObj["direction2"].isNull() ){
               qDebug()<<"direction2 array değil";
           }else{
               QJsonArray direction2 = existingLineObj["direction2"].toArray();
               QList<endPointsClass::station*> listStations;
           for(int k =0; k<direction2.size();++k){
               QJsonObject station = direction2.at(k).toObject();
               if(station.contains("id") && station.contains("latitude") && station.contains("longitude") && station.contains("name")){
                       endPointsClass::station* newStation = new  endPointsClass::station;
                       newStation->id = QString::number(station["id"].toInt());
                       newStation->latitude = QString::number(station["latitude"].toDouble());
                       newStation->longitude = QString::number(station["longitude"].toDouble());
                       newStation->name = station["name"].toString();
                       //qDebug()<<newStation->id<<" "<<newStation->name<<" "<<newStation->latitude << " "<< newStation->longitude;
                       listStations.append(newStation);
               }else{
                     endPoints->setErrCode("-readJSON-"+ID+"hat numarası yön 2 verisi için ID,enlem,boylam,isim alt üyeleri eksik, JSON okunamıyor. ");
                    statJson = false;
               }
            }
           if(listStations.size() == direction2.size()){
               if(listStations.size()>0){
                endPoints->addItemStations(ID,"2",listStations);
               }
           }else{
                qDebug()<<"-readJSON-"<<ID<<"hat numarası yön 2 verisi eksik okundu. ";
                endPoints->setErrCode("-readJSON-"+ID+"hat numarası yön 2 verisi eksik okundu. ");
                return false;
           }

           }
        }
        QFile debug(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/debug.txt");
        if(debug.open(QIODevice::WriteOnly)){
            QTextStream out(&debug);
           QMap<QString,QList<endPointsClass::station*>>::iterator itrMap;
            for(itrMap = endPoints->allLineStations.begin();(itrMap!=endPoints->allLineStations.end()); ++itrMap){
                for(endPointsClass::station* b : itrMap.value()){
                    out<<itrMap.key()<<" "<< b->name <<" "<<b->id<<" "<<b->latitude<<" "<<b->longitude<<Qt::endl;
                }
           }
            debug.close();
        }
    } else {

        this->endPoints->setErrCode("-readJSON- dataStations.json açılamadı");
        return false;
    }
    return statJson;
}

bool workerObject::readLineLIST(bool useBackup)
{
    QFile file("C:/appKYS_Pis/PISStations/dataLines.csv");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream *lines = new QTextStream(&file);
        quint8 lineNumber=0;
        this->lines.clear();
        while(!lines->atEnd()){
                QString line = lines->readLine();
               if(lineNumber>0){
                    this->lines.append(line.split(","));
               }
           lineNumber++;
        }
        bool hasMember = (this->lines.size()>0);
        bool isNumber = true;
        bool isRange = true;
        for(const QString& lineId : this->lines){
           bool isThisNumber;
           lineId.toDouble(&isThisNumber);
           if(!isThisNumber){
                    isNumber = false;
           }else{
                    if(!(lineId.toDouble()>0 && lineId.toDouble()<32535)){
                   isRange = false;
                    }
           }
        }
        if(!(isNumber && isRange && hasMember)){
            this->endPoints->setErrCode("-readLineLIST-Okunan hat bilgileri anlamsız.");
            QString backupPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataLines.csv";
            QFile backupFile(backupPath);
            if(backupFile.exists()){
                    if(backupFile.open(QIODevice::ReadOnly)){
                        QTextStream *lines = new QTextStream(&backupFile);
                        quint8 lineNumber=0;
                        this->lines.clear();
                        while(!lines->atEnd()){
                            QString line = lines->readLine();
                            if(lineNumber>0){
                                this->lines.append(line.split(","));
                            }
                            lineNumber++;
                        }
                        this->endPoints->setErrCode("-readLineLIST-dataLines.csv yedek konumundan kullanıldı.");
                        return true;
                    }else{
                        this->endPoints->setErrCode("-readLineLIST-dataLines.csv yedek konumunda bulunmuyor.");
                        return false;
                    }
            }else{
                return false;
            }
        }else{
            QString sourcePath = "C:/appKYS_Pis/PISStations/dataLines.csv";
            QString destinationPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataLines.csv";
            compareAndCopyFile(sourcePath, destinationPath);
            this->endPoints->setErrCode("-readLineLIST-dataLines.csv dosyası okundu ve yedek liste güncellendi");
            return true;
        }
    }else{
        if(useBackup){
            QString backupPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataLines.csv";
            QFile backupFile(backupPath);
            if(backupFile.exists()){
                if(backupFile.open(QIODevice::ReadOnly)){
                    QTextStream *lines = new QTextStream(&backupFile);
                    quint8 lineNumber=0;
                    this->lines.clear();
                    while(!lines->atEnd()){
                            QString line = lines->readLine();
                            if(lineNumber>0){
                                this->lines.append(line.split(","));
                            }
                            lineNumber++;
                    }
                    QString destinationPath = "C:/appKYS_Pis/PISStations/dataLines.csv";
                    QString sourcePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/appKYS_Pis/Backups/dataLines.csv";
                    compareAndCopyFile(sourcePath, destinationPath);
                    this->endPoints->setErrCode("-readLineLIST-dataLines.csv dosyası okunamadığı için yedek liste aktarıldı.");
                    return true;
                }else{
                    this->endPoints->setErrCode("-readLineLIST-dataLines.csv dosyası okunamadı ve yedek liste de açılamadı.");
                    return false;
                }
            }else{
                this->endPoints->setErrCode("-readLineLIST-dataLines.csv dosyası okunamadı ve yedek liste bulunmuyor");
                return false;
            }
        }else{
            this->endPoints->setErrCode("-readLineLIST-dataLines.csv dosyası okunamadı ve yedek liste güncelleme modunda kullanılamaz.");
            return false;
        }
    }
}

void workerObject::rwComApp()
{
    //READ
    QFile appToPis("C:/appKYS_Pis/PISCom/ApptoPIS.json");


    if (appToPis.exists()) {
        if (!appToPis.open(QIODevice::ReadOnly)) {
            this->endPoints->setErrCode("-rwComApp-ApptoPIS.json dosyası okunamadı,APP ile haberleşme sağlanamaz");
        }
        QByteArray IIdata = appToPis.readAll();
        appToPis.close();
        QJsonDocument IIDataJson = QJsonDocument::fromJson(IIdata);
        if(!IIDataJson.isObject()){
            this->endPoints->setErrCode("-rwComApp-ApptoPIS.json formatı uygun değil");
            if (appToPis.open(QIODevice::WriteOnly)) {
                QJsonObject fixedObject;
                fixedObject.insert("VehicleID",0);
                fixedObject.insert("LifeSign",0);
                fixedObject.insert("GPSOk","false");
                fixedObject.insert("GPSLongtitude",0);
                fixedObject.insert("GPSLatitude",0);
                fixedObject.insert("VehicleSpeed",0);
                fixedObject.insert("AnyDoorOpen","true");
                fixedObject.insert("ProgressUpdate","true");
                QJsonDocument QJsonDocument(fixedObject);
                appToPis.write(QJsonDocument.toJson());
                appToPis.close();
            }
        }else{
            QJsonObject IIDataObj = IIDataJson.object();
            if(IIDataObj.contains("LifeSign")){
                checkLifeSign(this->endPoints->iiCom.LifeSign,(unsigned int)IIDataObj["LifeSign"].toInt());
                this->endPoints->iiCom.LifeSign = IIDataObj["LifeSign"].toInt();
            }else{
                this->failCounterLifeSign = 404;
                this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> LifeSign bulunamadı.");
            }
            bool comOK = this->failCounterLifeSign < 6;
            if(comOK){
                if(IIDataObj.contains("VehicleID")){
                    this->endPoints->iiCom.VehicleID = IIDataObj["VehicleID"].toInt();
                    //qDebug()<<"VehicleID"<<this->endPoints->iiCom.VehicleID ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> VehicleID bulunamadı.");
                }
                if(IIDataObj.contains("GPSOk")){
                    this->endPoints->iiCom.GPSOk = IIDataObj["GPSOk"].toBool();
                    qDebug()<<"GPSOk"<<this->endPoints->iiCom.GPSOk ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> GPSOk bulunamadı.");
                }
                if(IIDataObj.contains("GPSLongtitude")){
                    this->endPoints->iiCom.GPSLongtitude = IIDataObj["GPSLongtitude"].toDouble();
                    //qDebug()<<"GPSLongtitude"<<this->endPoints->iiCom.GPSLongtitude ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> GPSLongtitude bulunamadı.");
                }
                if(IIDataObj.contains("GPSLatitude")){
                    this->endPoints->iiCom.GPSLatitude = IIDataObj["GPSLatitude"].toDouble();
                    //qDebug()<<"GPSLatitude"<<this->endPoints->iiCom.GPSLatitude ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> GPSLatitude bulunamadı.");
                }
                if(IIDataObj.contains("VehicleSpeed")){
                    this->endPoints->iiCom.VehicleSpeed = IIDataObj["VehicleSpeed"].toInt();
                    //qDebug()<<"VehicleSpeed"<<this->endPoints->iiCom.VehicleSpeed ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> VehicleSpeed bulunamadı.");
                }
                if(IIDataObj.contains("AnyDoorOpen")){
                    this->endPoints->iiCom.AnyDoorOpen = IIDataObj["AnyDoorOpen"].toBool();
                    //qDebug()<<"AnyDoorOpen"<<this->endPoints->iiCom.AnyDoorOpen ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> AnyDoorOpen bulunamadı.");
                }
                if(IIDataObj.contains("ProgressUpdate")){
                    this->endPoints->iiCom.ProgressUpdate = IIDataObj["ProgressUpdate"].toBool();
                    //qDebug()<<"ProgressUpdate"<<this->endPoints->iiCom.ProgressUpdate ;
                }else{
                    this->endPoints->setErrCode("-rwComApp-ApptoPIS.json -> ProgressUpdate bulunamadı.");
                }
            }else{
                if(this->endPoints->comAppOK()){
                    this->endPoints->setErrCode("-rwComApp- LifeSign değişmiyor,APP ile haberleşme hatası");
                }
            }
            this->endPoints->setComAppOK(comOK);
        }


    }else{
        this->endPoints->setErrCode("-rwComApp-ApptoPIS.json dosyası yok,APP ile haberleşme sağlanamaz, ancak dosya oluşturuldu.");
        if (appToPis.open(QIODevice::WriteOnly)) {
            QJsonObject fixedObject;
            fixedObject.insert("VehicleID",0);
            fixedObject.insert("LifeSign",0);
            fixedObject.insert("GPSOk","false");
            fixedObject.insert("GPSLongtitude",0);
            fixedObject.insert("GPSLatitude",0);
            fixedObject.insert("VehicleSpeed",0);
            fixedObject.insert("AnyDoorOpen","true");
            fixedObject.insert("ProgressUpdate","true");
            QJsonDocument QJsonDocument(fixedObject);
            appToPis.write(QJsonDocument.toJson());
            appToPis.close();
        }
    }

    //WRITE
    if(this->endPoints->ioCom.LifeSign>65535){
        this->endPoints->ioCom.LifeSign=0;
    }else{
        ++this->endPoints->ioCom.LifeSign;
    }
    QFile pisToApp("C:/appKYS_Pis/PISCom/PIStoApp.json");

    if(!pisToApp.open(QIODevice::WriteOnly)){
        this->endPoints->setErrCode("-rwComApp-PIStoApp.json dosyası okunamadı,APP'a veri paylaşılamıyor");
    }else{
        QJsonObject sendObject;
        sendObject.insert("LifeSign",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.LifeSign))));
        sendObject.insert("VehicleID",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.VehicleID))));
        sendObject.insert("ActiveLineInfo",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.ActiveLineInfo))));
        sendObject.insert("ActiveDirection",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.ActiveDirection))));
        sendObject.insert("ActiveStation",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.ActiveStation))));
        sendObject.insert("ActiveStationId",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.ActiveStationId))));
        sendObject.insert("NextStation",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.NextStation))));
        sendObject.insert("NextStationId",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.NextStationId))));
        sendObject.insert("ActiveAnounce",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.ActiveAnounce))));
        sendObject.insert("ActiveCommercial",(QJsonValue::fromVariant(QVariant::fromValue(this->endPoints->ioCom.ActiveCommercial))));
        QJsonDocument QJsonDocument(sendObject);
        pisToApp.write(QJsonDocument.toJson());
        pisToApp.close();
    }



}

void workerObject::cycleCall()
{

    // Setters

    if(this->endPoints->errList.size()>LOG_SAVE_COUNTER){
        saveLogs();
    }
    //Use communication parameters
    this->endPoints->setStateNoGpsInfo(!checkGPS());
    this->endPoints->setactualLatitude(QString::number(this->endPoints->iiCom.GPSLatitude));
    this->endPoints->setactualLongitude(QString::number(this->endPoints->iiCom.GPSLongtitude));



    //Cycle operation check
    if(cycleCheckRead){
        if(processBlockedConnection){
            if(checkConnection()){
                this->readStations();
            }
        }
        if(processBlockedFileLines){
            if(checkFileLines() && readLineLIST(false)){
                this->readStations();
            }
        }
        if(processBlockedService){
            if(checkService()){
                this->readStations();
            }
        }
    }
    if(cycleCheckUpdate){
        if(processBlockedConnection){
            if(checkConnection()){
                this->updateList();
            }
        }
        if(processBlockedFileLines){
            if(checkFileLines() && readLineLIST(false)){
                this->updateList();
            }
        }
        if(processBlockedService){
            if(checkService()){
                this->updateList();
            }
        }
    }
    //Cycle operation exits




}

void workerObject::updateList()
{
    if(this->endPoints->updateStations()){
        bool updateComplete = false;
        bool processBlockedFileLines = !readLineLIST(false);

        if(!processBlockedFileLines){
            if(!((processBlockedService = !(checkConnection())) || (processBlockedConnection= !(checkService())))){
                sendHttpReq();
                updateComplete = readJSON(false);
            }else{
                this->endPoints->setErrCode("-updateList- Bağlantı sorunu veya servis çalışmadığı için güncelleme yapılamadı.");
                updateComplete = false;
            }
        }else{
            readLineLIST(true);
            this->endPoints->setErrCode("-updateList- dataLines.csv bulunamadığı için güncelleme yapılamadı.");
            updateComplete = false;
        }
        this->enableCycleCheckUpdate(!updateComplete);
        if(updateComplete){
            emit this->endPoints->updateSuccesfull();
            this->endPoints->setUpdateStations(true);
        }else{
            emit this->endPoints->updateFailed();
        }
        this->endPoints->setDataImported(updateComplete);
        readVideoFolder();
    }


}
void workerObject::beginSpecificStation(QString stationID)
{
    QString currentStationID,nextStationID = "";
    bool foundFlag = false;
    unsigned int index =0;
    for(endPointsClass::station Obj : this->endPoints->currentLineStations){
        if((foundFlag) && (nextStationID=="")){
            nextStationID=Obj.id;
            break;
        }else{
            if(Obj.id == stationID){
                currentStationID = Obj.id;
                index = this->endPoints->currentLineStations.indexOf(Obj);
                foundFlag = true;
            }
        }
    }
    this->endPoints->currentViewFour.clear();
        for(unsigned i=index;i<index+4 ;++i ){
                this->endPoints->currentViewFour.append(this->endPoints->currentLineStations.at(i).name);
        //qDebug()<<this->endPoints->currentLineStations.at(i).name;
        }
    emit endPoints->updateViewFour();
    this->endPoints->setCurrentStation(currentStationID);
    this->endPoints->setNextStation(nextStationID);
    endPoints->setCurrentStationOrder(index);
}
double workerObject::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double earthRadius = 6371000; // Earth radius
    lat1 = qDegreesToRadians(lat1);
    lon1 = qDegreesToRadians(lon1);
    lat2 = qDegreesToRadians(lat2);
    lon2 = qDegreesToRadians(lon2);

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a = qSin(dLat / 2) * qSin(dLat / 2) +
               qCos(lat1) * qCos(lat2) *
                   qSin(dLon / 2) * qSin(dLon / 2);
    double c = 2 * qAtan2(qSqrt(a), qSqrt(1 - a));

    double distance = qAbs(earthRadius * c);
    return distance;
}
void workerObject::handleLineSelection()
{

    if(this->endPoints->lineSelected()){
        if(this->endPoints->stateNoGpsInfo()){
            beginSpecificStation(this->endPoints->currentLineStations.at(0).id);
            this->endPoints->setLineSelected(false);
            this->endPoints->setCurrentLine(this->endPoints->selectedLine.replace("_","->"));
        }else{
            qDebug()<<"handlelineselection - else";
            double minDistance = std::numeric_limits<double>::max(); // Çok büyük bir başlangıç değeri
            endPointsClass::station searchItem;

            for (const endPointsClass::station Obj : this->endPoints->currentLineStations) {
                double currentDistance = calculateDistance(Obj.latitude.toDouble(), Obj.longitude.toDouble(), this->endPoints->actualLatitude().toDouble(), this->endPoints->actualLongitude().toDouble());
                if (currentDistance < minDistance) {
                    minDistance = currentDistance;
                    searchItem = Obj;
                }
            }
            //qDebug()<<"İstasyon ID'si "<<searchItem.id;
            this->endPoints->getConfirmationCurrentStation(searchItem.id);
        }
    }
}

void workerObject::confirmLineSelection()
{
    beginSpecificStation(this->endPoints->stationConfirmed());
    this->endPoints->setLineSelected(false);
    this->endPoints->setCurrentLine(this->endPoints->selectedLine.replace("_","->"));
}
