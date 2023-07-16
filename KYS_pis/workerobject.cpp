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
#include <QJsonObject>
#include <QJsonDocument>

#define COM_INTERVAL 1000
#define CYCLETIMER_INTERVAL 500
workerObject::workerObject(QObject *parent, endPointsClass *endPoints)
{
    this->endPoints = endPoints;

    {
        QString path = "C:/appKYS_Pis/PISStations";
        QDir directory(path);

        if (directory.exists()) {
           //nothing to do
        } else {
           directory.mkpath(path);
           this->endPoints->setErrCode("PISStations mevcut değil, oluşturuldu");
        }
    }
    {
        QString path = "C:/appKYS_Pis/PISVideos";
        QDir directory(path);

        if (directory.exists()) {
           //nothing to do
        } else {
           directory.mkpath(path);
           this->endPoints->setErrCode("PISVideos mevcut değil, oluşturuldu");
        }
    }
    {
        QString path = "C:/appKYS_Pis/PISSpecialAnounce";
        QDir directory(path);

        if (directory.exists()) {
           //nothing to do
        } else {
           directory.mkpath(path);
           this->endPoints->setErrCode("PISSpecialAnounce mevcut değil, oluşturuldu");
        }
    }
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
    QString filePath = "C:/appKYS_Pis/PISStations/dataLines.csv"; // Kontrol edilecek dosyanın yolu

    QFile file(filePath);
    if (file.exists()) {
        //this->endPoints->setErrCode("dataLines.csv mevcut.");
    } else {
        this->endPoints->setErrCode("dataLines.csv mevcut değil,durak bilgileri alınamıyor destek ile iletişime geçin");
        this->endPoints->setStateNoStationInfo(true);
        this->endPoints->setStateDispTextOnStationArea(true);
    }


}

workerObject::~workerObject()
{
    QString path= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir directory(path+"/appKYS_Pis/Log");
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("Dyyyy_MM_dd_Shh_mm_ss");
    if(directory.exists()){
        // do nothing
    }else{
        directory.mkpath(path+"/appKYS_Pis/Log");
        this->endPoints->setErrCode("log dosyası bulunamadı ve oluşturuldu.");
    }
    QFile logFile(path+"/appKYS_Pis/Log/"+formattedDateTime+"_logs.txt");

    if (!logFile.open(QIODevice::WriteOnly| QIODevice::Truncate )){
         this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
    }else{
        QTextStream out(&logFile);
         this->endPoints->setErrCode("Kayıt defterine kayıt edildi.");
         foreach(QString logLine , this->endPoints->errList){
           out<<logLine<<Qt::endl;
        }

        logFile.close();
    }
    QFile logFile2("C:/appKYS_Pis/PISLog/"+formattedDateTime+"_logs.txt");


    if (!logFile2.open(QIODevice::WriteOnly| QIODevice::Truncate )){
         this->endPoints->setErrCode("Yapılan değişiklikler kayıt defterine işlenemedi");
    }else{
        QTextStream out2(&logFile2);
        foreach(QString logLine2 , this->endPoints->errList){
           out2<<logLine2<<Qt::endl;
        }
        logFile2.close();
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
        return true;
} else {
    // İnternet bağlantısı yok veya erişim hatası
        return false;
}

delete reply;


}

bool workerObject::checkFolderStructure()
{
    bool lineCsvOK,JsonFileOK,selectedLineSoundsOk;

{       //Is lineCsvOK ?
        QString filePath = "C:/appKYS_Pis/PISStations/dataLines.csv"; // Kontrol edilecek dosyanın yolu

        QFile file(filePath);
        if (file.exists()) {
           lineCsvOK = true;
        } else {
           lineCsvOK = false;
        }
}
{       //Is JsonFileOK ?
        QString filePath = "C:/appKYS_Pis/PISStations/dataStations.json"; // Kontrol edilecek dosyanın yolu

        QFile file(filePath);
        if (file.exists()) {
           JsonFileOK = true;
        } else {
           JsonFileOK = false;
        }
}
{       //Is selectedLineSoundsOk ?
        QString filePath = "C:/appKYS_Pis/PISStations/dataStations.http"; // Kontrol edilecek dosyanın yolu

        QFile file(filePath);
        if (file.exists()) {
           JsonFileOK = true;
        } else {
           JsonFileOK = false;
        }
}
    return lineCsvOK && JsonFileOK && selectedLineSoundsOk;
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

void workerObject::sendHttpReq()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl("https://kaktusmobile.kayseriulasim.com.tr/api/LineStops?lineId=643&direction=1"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonRequest;

    QByteArray requestData = QJsonDocument(jsonRequest).toJson();

    QNetworkReply *reply = manager->post(request, requestData);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

            QFile file("response.json");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(jsonResponse.toJson());
                file.close();
                emit doneReqHTTP();
            }
        } else {
            this->endPoints->setErrCode("HTTP isteği başarısız"+reply->errorString());
        }
        reply->deleteLater();
    });
}

void workerObject::readJSON()
{

}

void workerObject::readLineLIST()
{
    QFile file("C:/appKYS_Pis/PISStations/dataLines.csv");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream *lines = new QTextStream(&file);
        quint8 lineNumber=0;
        while(!lines->atEnd()){
           if (lineNumber > 0){
               QString line = lines->readLine();
               this->endPoints->setErrCode("Hatlar başarıyla okundu.Hatlar"+line);
               this->lines = line.split(",");
           }
           ++lineNumber;
        }
    }else{
        checkFolderStructure();
    }
}

void workerObject::rwComApp()
{

}

void workerObject::cycleCall()
{
    emit this->endPoints->setstateNetwork(this->checkConnection());
    emit this->endPoints->setStateNoFolderFound(checkFolderStructure());


}
