//
//this->endPoints->setErrCode("İnternet bağlantısı mevcut değil.");
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

#define COM_INTERVAL 1000
#define CYCLETIMER_INTERVAL 500




workerObject::workerObject(QObject *parent, endPointsClass *endPoints)
{
    this->endPoints = endPoints;

    checkFolderStations();
    checkFolderVideo();
    checkFolderAudioForLines();

}

workerObject::~workerObject()
{
    {
        QString path = "C:/appKYS_Pis/PISLog";
        QDir directory(path);

        if (directory.exists()) {
           //nothing to do
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


    QFile logFile(path+"/appKYS_Pis/Log/"+formattedDateTime+"_logs.PISLog");
    if(logFile.exists()){
        if (!logFile.open(QIODevice::Append)){
            this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
        }else{

            QTextStream out(&logFile);
             this->endPoints->setErrCode("Kayıt defterine kayıt edildi.");
             foreach(QString logLine , this->endPoints->errList){
                 if(!logLine.isEmpty()){
                    out<<logLine<<Qt::endl;
                 }
            }
            logFile.close();
        }
    }else{
        if (!logFile.open(QIODevice::WriteOnly| QIODevice::Truncate )){
             this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
        }else{
            QTextStream out(&logFile);
             this->endPoints->setErrCode("Kayıt defterine kayıt edildi.");
             foreach(QString logLine , this->endPoints->errList){
                if(!logLine.isEmpty()){
                    out<<logLine<<Qt::endl;
                }
            }
            logFile.close();
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

bool workerObject::checkConnection()
{
QNetworkAccessManager manager;
QNetworkRequest request(QUrl("https://www.google.com"));

QNetworkReply *reply = manager.get(request);

if (reply->error() == QNetworkReply::NoError) {
    // İnternet bağlantısı mevcut
        this->endPoints->setStateNetwork(true);
        return true;
} else {
    // İnternet bağlantısı yok veya erişim hatası
        this->endPoints->setStateNetwork(false);
        return false;
}

delete reply;

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
           this->linesOK = true;
           enableCycleCheckFileLines(false);
        } else {
           lineCsvOK = false;
           this->linesOK = false;
           enableCycleCheckFileLines(true);
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
                    qDebug()<<" lineIdFoundInn: " <<lineIdFoundInn;
               }
               if(!lineIdFoundInn){
                    lineIdNotFoundExt = true;
               }qDebug()<<" lineIdFoundInn: " <<lineIdFoundInn;
           }
           if(lineIdNotFoundExt){
               jsonFileOK = false;
           }
        } else {
           jsonFileOK = false;
        }


this->JSONOK = jsonFileOK;
qDebug()<<"stat: " <<jsonFileOK;
return jsonFileOK;
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

void workerObject::enableCycleCheckFileLines(bool cycleCheckFileLines)
{
    this-> cycleCheckFileLines = cycleCheckFileLines;
}

void workerObject::enableCycleCheckJson(bool cycleCheckJson)
{
    this-> cycleCheckJson = cycleCheckJson;
}


void workerObject::enableCycleCheckVideos(bool cycleCheckVideos)
{
    this-> cycleCheckVideos = cycleCheckVideos;
}

void workerObject::enableCycleConnectionCheck(bool cycleCheckConnection)
{
    this-> cycleCheckConnection = cycleCheckConnection;
}

void workerObject::enableCycleAuidoCheck(bool cycleCheckAuido)
{
    this-> cycleCheckConnection = cycleCheckAuido;
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

    QObject::connect(this->endPoints,&endPointsClass::updateStationsChanged,this,&workerObject::readLineLIST,Qt::AutoConnection);
    QObject::connect(this,&workerObject::donereadLineList,this,&workerObject::sendHttpReq,Qt::AutoConnection);
    QObject::connect(this,&workerObject::doneReqHTTP,this,&workerObject::readJSON,Qt::AutoConnection);
    QObject::connect(this,&workerObject::doneReadJSON,this->endPoints,&endPointsClass::setUpdatingStations,Qt::AutoConnection);

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
    QObject::disconnect(this->endPoints,&endPointsClass::updateStationsChanged,this,&workerObject::readLineLIST);
    QObject::disconnect(this,&workerObject::donereadLineList,this,&workerObject::sendHttpReq);
    QObject::disconnect(this,&workerObject::doneReqHTTP,this,&workerObject::readJSON);
    QObject::disconnect(this,&workerObject::doneReadJSON,this->endPoints,&endPointsClass::setUpdatingStations);
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

    QJsonObject mergedJson;

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
                   QJsonArray directionArray;
                   directionArray.append(json1.array());
                   lineObj.insert("direction1", directionArray);
               }
               if (json2.isEmpty()) {
                   qDebug() << "Yön bulunamadı!";
                   lineObj.insert("direction2", QJsonArray());
               } else {
                   QJsonArray directionArray;
                   directionArray.append(json2.array());
                   lineObj.insert("direction2", directionArray);
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
}

void workerObject::readJSON()
{
    QString filePath = "C:/appKYS_Pis/PISStations/dataStations.json"; // Kontrol edilecek dosyanın yolu

    QFile file(filePath);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly)) {
           this->endPoints->setErrCode("-readJSON- JSON dosyası açılamadı");
        }
        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument fileDoc = QJsonDocument::fromJson(fileData);
        if (!fileDoc.isArray()) {
           this->endPoints->setErrCode("-readJSON- JSON verisi geçersiz");
        }

        QJsonArray existingDataStations = fileDoc.array();
        bool lineIdFound = false;
        for (int i = 0; i < existingDataStations.size(); ++i) {
           QJsonObject existingLineObj = existingDataStations.at(i).toObject();
           if (existingLineObj.contains("lineId")) {
               lineIdFound = true;

           }
        }
    } else {

    }
}

void workerObject::readLineLIST()
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
                    this->endPoints->setErrCode("Hatlar başarıyla okundu.Hatlar"+line);
               }
           lineNumber++;
        }
        if(lineNumber>0){
           emit this->donereadLineList();
        }else
           enableCycleCheckFileLines(true);
    }else{
        checkFileLines();
    }
}

void workerObject::rwComApp()
{

}

void workerObject::cycleCall()
{
    emit this->endPoints->setStateNetwork(this->checkConnection());
    if(cycleCheckFileLines){
        enableCycleCheckFileLines(!checkFileLines());
    }
    if(cycleCheckJson){
        bool checkJson = checkFileJson();
        enableCycleCheckJson(!checkJson);
        if(checkJson){
           readLineLIST();
        }
    }
}
