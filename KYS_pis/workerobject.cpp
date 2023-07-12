//https://kaktusmobile.kayseriulasim.com.tr/api/LineStops?lineId=643&direction=1
#include "workerobject.h"

#include <QFile>
#include <QDir>
workerObject::workerObject(QObject *parent, endPointsClass *endPoints)
{
    this->endPoints = endPoints;

    {
        QString path = "C:/appKYS_Pis/PISDuraklar";
        QDir directory(path);

        if (directory.exists("")) {
           //nothing to do
        } else {
           directory.mkpath("path");
           this->endPoints->seterrCode("PISDuraklar mevcut değil, oluşturuldu");
        }
    }
    {
        QString path = "C:/appKYS_Pis/PISVideolar";
        QDir directory(path);

        if (directory.exists("")) {
           //nothing to do
        } else {
           directory.mkpath("path");
           this->endPoints->seterrCode("PISVideolar mevcut değil, oluşturuldu");
        }
    }
    {
        QString path = "C:/appKYS_Pis/PISanonslar";
        QDir directory(path);

        if (directory.exists("")) {
           //nothing to do
        } else {
           directory.mkpath("path");
           this->endPoints->seterrCode("PISanonslar mevcut değil, oluşturuldu");
        }
    }
    QString filePath = "C:/appKYS_Pis/PISDuraklar/dataLines.csv"; // Kontrol edilecek dosyanın yolu

    QFile file(filePath);
    if (file.exists()) {
        this->endPoints->seterrCode("Dosya mevcut.");
    } else {
        this->endPoints->seterrCode("dataLines.csv mevcut değil,durak bilgileri alınamıyor destek ile iletişime geçin");
        this->endPoints->setStateNoStationInfo(true);
        this->endPoints->setStateDispTextOnStationArea(true);
    }

}

void workerObject::startObject()
{

}

void workerObject::stopObject()
{

}
