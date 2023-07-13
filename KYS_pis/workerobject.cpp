//https://kaktusmobile.kayseriulasim.com.tr/api/LineStops?lineId=643&direction=1
//
#include "workerobject.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>
#include <QTextStream>


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

void workerObject::startObject()
{
    timerOneSec = new QTimer(this);
    timerOneSec->setInterval(1000);
    QObject::connect(timerOneSec,&QTimer::timeout,this,&workerObject::writePistoApp,Qt::AutoConnection);
    QObject::connect(timerOneSec,&QTimer::timeout,this,&workerObject::readApptoPis,Qt::AutoConnection);
    QObject::connect(this->endPoints,&endPointsClass::updateStationsChanged,this,&workerObject::readJSON,Qt::AutoConnection);
    QObject::connect(this->endPoints,&endPointsClass::updateStationsChanged,this,&workerObject::readJSON,Qt::AutoConnection);
}

void workerObject::stopObject()
{



}
