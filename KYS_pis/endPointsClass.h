//this class is created to use communication between interface and backend

#ifndef ENDPOINTSCLASS_H
#define ENDPOINTSCLASS_H

#include "qdebug.h"
#include "qobject.h"
#include <QFile>
#include <QList>
#include <QDateTime>
#include <QMap>
#include <QDir>


class endPointsClass: public QObject{

    Q_OBJECT

    Q_PROPERTY(bool stateDispWatchOnVideoArea READ stateDispWatchOnVideoArea WRITE setStateDispWatchOnVideoArea NOTIFY stateDispWatchOnVideoAreaChanged)/*cyclecall*/
    Q_PROPERTY(bool stateDispTextOnStationArea READ stateDispTextOnStationArea WRITE setStateDispTextOnStationArea NOTIFY stateDispTextOnStationAreaChanged)/*cyclecall*/

    Q_PROPERTY(bool stateNoGpsInfo READ stateNoGpsInfo WRITE setStateNoGpsInfo NOTIFY stateNoGpsInfoChanged)/*cyclecall*/
    Q_PROPERTY(bool stateNoStationInfo READ stateNoStationInfo WRITE setStateNoStationInfo NOTIFY stateNoStationInfoChanged)/*cyclecall*/
    Q_PROPERTY(bool stateNetwork READ stateNetwork WRITE setStateNetwork NOTIFY stateNetworkChanged)
    Q_PROPERTY(QString errCode READ errCode WRITE setErrCode NOTIFY errCodeChanged)

    Q_PROPERTY(bool dataImported READ dataImported WRITE setDataImported NOTIFY dataImportedChanged)                    /*Set when data imported and data is free to use, UI should activate driver select area*/
    Q_PROPERTY(bool folderStructureOK READ folderStructureOK WRITE setFolderStructureOK NOTIFY folderStructureOKChanged)/**/
    Q_PROPERTY(bool updateStations READ updateStations WRITE setUpdateStations NOTIFY updateStationsChanged)
    Q_PROPERTY(bool comAppOK READ comAppOK WRITE setComAppOK NOTIFY comAppOKChanged);

    //Operational Datas
    Q_PROPERTY(bool lineSelected READ lineSelected WRITE setLineSelected NOTIFY lineSelectedChanged)
    Q_PROPERTY(bool selectionDone READ selectionDone WRITE setSelectionDone NOTIFY selectionDoneChanged)
    Q_PROPERTY(QString currentLine READ currentLine WRITE setCurrentLine NOTIFY currentLineChanged)
    Q_PROPERTY(QString currentStation READ currentStation WRITE setCurrentStation NOTIFY currentStationChanged)
    Q_PROPERTY(QString nextStation READ nextStation WRITE setNextStation NOTIFY nextStationChanged)
    Q_PROPERTY(unsigned lifeSign READ lifeSign WRITE setLifeSign NOTIFY lifeSignChanged)
    Q_PROPERTY(QString currentSpecialAnounce READ currentSpecialAnounce WRITE setCurrentSpecialAnounce NOTIFY currentSpecialAnounceChanged)
    Q_PROPERTY(unsigned currentStationOrder READ currentStationOrder WRITE setCurrentStationOrder NOTIFY currentStationOrderChanged)
    Q_PROPERTY(bool stateSpecialAnounceActive READ stateSpecialAnounceActive WRITE setStateSpecialAnounceActive NOTIFY stateSpecialAnounceActiveChanged)
    Q_PROPERTY(bool stateRegularAnounceActive READ stateRegularAnounceActive WRITE setStateRegularAnounceActive NOTIFY stateRegularAnounceActiveChanged)

    /*Confirmation*/
    Q_PROPERTY(QString stationConfirmed READ stationConfirmed WRITE setStationConfirmed NOTIFY StationConfirmedChanged)
    Q_PROPERTY(QString confirmStationID READ confirmStationID WRITE setConfirmStationID NOTIFY confirmStationIDChanged)

    /*Communication parameters*/
    Q_PROPERTY(QString vehicleSpeed READ vehicleSpeed WRITE setVehicleSpeed NOTIFY vehicleSpeedChanged)
    Q_PROPERTY(QString actualLongitude READ actualLongitude WRITE setactualLongitude NOTIFY actualLongitudeChanged)
    Q_PROPERTY(QString actualLatitude READ actualLatitude WRITE setactualLatitude NOTIFY actualLatitudeChanged)
    Q_PROPERTY(bool anyDoorOpen READ anyDoorOpen WRITE setAnyDoorOpen NOTIFY anyDoorOpenChanged)
    Q_PROPERTY(bool updateInProgress READ updateInProgress WRITE setUpdateInProgress NOTIFY updateInProgressChanged)
    Q_PROPERTY(QString vehicleID READ vehicleID WRITE setVehicleID NOTIFY vehicleIDChanged)

    Q_PROPERTY(QString activeCommercial READ activeCommercial WRITE setActiveCommercial NOTIFY activeCommercialChanged)
    Q_PROPERTY(QString activeAnounce READ activeAnounce WRITE setActiveAnounce NOTIFY activeAnounceChanged)


    Q_PROPERTY(QString playSound READ playSound WRITE setPlaySound NOTIFY playSoundChanged)
    Q_PROPERTY(QString playSoundStations READ playSoundStations WRITE setPlaySoundStations NOTIFY playSoundStationsChanged)
    Q_PROPERTY(bool pauseAnounce READ pauseAnounce WRITE setPauseAnounce NOTIFY pauseAnounceChanged)
    Q_PROPERTY(bool periodicalAnounceAllowed READ periodicalAnounceAllowed WRITE setPeriodicalAnounceAllowed NOTIFY periodicalAnounceAllowedChanged)
public:
    struct IIData{
        unsigned VehicleID;
        unsigned LifeSign;
        double VehicleSpeed;
        bool AnyDoorOpen;
        bool ProgressUpdate;
    };

    struct IOData{
        unsigned LifeSign;
        unsigned VehicleID;
        QString ActiveLineInfo;
        QString ActiveStation;
        unsigned ActiveStationId;
        QString NextStation;
        unsigned NextStationId;
        QString ActiveAnounce;
        QString ActiveCommercial;
        bool GPSOk;
        double GPSLongtitude;
        double GPSLatitude;
    };
    struct anounce{
        QString name;
        bool periodical;
        QString period;
        QTime lastPlay;
    };

    IIData iiCom;
    IOData ioCom;
    struct station;
    struct videos;
    /*Application definitions*/
    QString viewLine;
    QString selectedLine;
    /*Application definitions*/
    QList<QString> errList{0};
    QMap<QString,QList<station*>> allLineStations;
    QList<station> currentLineStations;
    QList<QString> currentViewFour;
    QList<videos> videoList;
    QList<anounce*> periodicAnounceList;
    QList<QString> anounceList;
    explicit endPointsClass(QObject *parent = nullptr);
    ~endPointsClass();



    bool stateNoFolderFound() const;
    void setStateNoFolderFound(bool newStateNoFolderFound);

    bool stateDispWatchOnVideoArea() const;
    void setStateDispWatchOnVideoArea(bool newStateDispWatchOnVideoArea);

    bool stateDispTextOnStationArea() const;
    void setStateDispTextOnStationArea(bool newStateDispTextOnStationArea);

    bool stateSpecialAnounceActive() const;
    void setStateSpecialAnounceActive(bool newStateSpecialAnounceActive);

    bool stateRegularAnounceActive() const;
    void setStateRegularAnounceActive(bool newStateRegularAnounceActive);

    bool stateNoGpsInfo() const;
    void setStateNoGpsInfo(bool newStateNoGpsInfo);

    bool stateNoStationInfo() const;
    void setStateNoStationInfo(bool newStateNoStationInfo);

    QString errCode() const;
    void setErrCode(const QString &newErrCode);

    bool updateStations() const;
    void setUpdateStations(bool newUpdateStations);

    bool stateNetwork() const;
    void setStateNetwork(bool newStateNetwork);

    QString currentLine() const;
    void setCurrentLine(const QString &newCurrentLine);

    QString currentStation() const;
    void setCurrentStation(const QString &newCurrentStation);

    QString currentSpecialAnounce() const;
    void setCurrentSpecialAnounce(const QString &newCurrentSpecialAnounce);


    QString nextStation() const;
    void setnextStation(const QString &newNextStation);

    void setNextStation(const QString &newNextStation);

    bool lineSelected() const;
    void setLineSelected(bool newLineSelected);

    bool dataImported() const;
    void setDataImported(bool newDataImported);

    bool folderStructureOK() const;
    void setFolderStructureOK(bool newFolderStructureOK);

    void addItemStations(QString ID, QString dir, QList<station *> );


    QString actualLongitude() const;
    void setactualLongitude(const QString &newactualLongitude);

    QString actualLatitude() const;
    void setactualLatitude(const QString &newactualLatitude);

    bool comAppOK() const;
    void setComAppOK(bool newComAppOK);

    unsigned int currentStationOrder() const;
    void setCurrentStationOrder(unsigned int newcurrentStationOrder);

    /*Confimation*/

    QString stationConfirmed() const;
    void setStationConfirmed(const QString &newStationConfirmed);

    QString confirmStationID() const;
    void setConfirmStationID(const QString &newConfirmStationID);

    QString vehicleSpeed() const;
    void setVehicleSpeed(const QString &newVehicleSpeed);

    bool anyDoorOpen() const;
    void setAnyDoorOpen(bool newAnyDoorOpen);

    bool updateInProgress() const;
    void setUpdateInProgress(bool newUpdateInProgress);

    QString vehicleID() const;
    void setVehicleID(const QString &newVehicleID);

    bool selectionDone() const;
    void setSelectionDone(bool newSelectionDone);

    QString playSound() const;
    void setPlaySound(const QString &newPlaySound);

    bool pauseAnounce() const;
    void setPauseAnounce(bool newPauseAnounce);

    QString playSoundStations() const;
    void setPlaySoundStations(const QString &newPlaySoundStations);

    QString activeCommercial() const;
    void setActiveCommercial(const QString &newActiveCommercial);

    QString activeAnounce() const;
    void setActiveAnounce(const QString &newActiveAnounce);

    unsigned int lifeSign() const;
    void setLifeSign(unsigned int newLifeSign);

    bool periodicalAnounceAllowed() const;
    void setPeriodicalAnounceAllowed(bool newPeriodicalAnounceAllowed);

signals:
    void stateNoFolderFoundChanged();

    void stateDispWatchOnVideoAreaChanged();

    void stateDispTextOnStationAreaChanged();

    void stateSpecialAnounceActiveChanged();

    void stateRegularAnounceActiveChanged();

    void stateNoGpsInfoChanged();

    void stateNoStationInfoChanged();

    void errCodeChanged();

    void updateStationsChanged();

    void updatingStationsChanged();

    void stateNetworkChanged();

    void currentLineChanged();

    void currentStationChanged();

    void currentSpecialAnounceChanged();

    void nextStationChanged();

    void lineSelectedChanged();

    void dataImportedChanged();

    void folderStructureOKChanged();

    void actualLongitudeChanged();

    void actualLatitudeChanged();

    void comAppOKChanged();

    void updateSuccesfull();

    void updateFailed();

    /*application Signals*/
    void anounceCurrentStation();

    void anounceNextStation();

    void loadViewFour();

    void updateViewFour();

    void confirmPopup();

    void currentStationOrderChanged();

    void StationConfirmedChanged();

    void confirmStationIDChanged();

    void confirmationIDChanged();

    void videoFolderUpdated();

    void anounceFolderUpdated();

    void vehicleSpeedChanged();

    void anyDoorOpenChanged();

    void updateInProgressChanged();

    void vehicleIDChanged();

    void selectionDoneChanged();

    void playSoundChanged();

    void pauseAnounceChanged();

    void playSoundStationsChanged();

    void activeCommercialChanged();

    void activeAnounceChanged();

    void lifeSignChanged();

    void periodicalAnounceAllowedChanged();

public slots:
    void clearList();
    /*Application functions*/
    QList<QString> getLineList();
    QList<QString> getStations();
    void selectviewLine(QString lineID);
    void selectLine();
    void getConfirmationCurrentStation(QString currentStationName);
    QString getOffsetStation(QString currentStationID,int offset);
    void confirmStationSelection(QString currentStationID);
    void increaseConfirmationStation();
    void deacreaseConfirmationStation();
    QString getStationName(QString stationID);
    void cancelLineSelection();
    /*Video*/
    void logVideoPlay(QString mediaId);
    void logMediaPlay(QString mediaName);
    void setVideoUnavailable();
    void setVideoAvailable();

    /*Direction*/
    QString getViewFourMember(unsigned index);

    QString getPathAudio(QString stationID);

    QList<QString> getAnounceList();

    /*Periodic Anounce*/
    void addPeriodicAnounceList(QString anounceAdd);
    void removePeriodicAnounceList(QString anounceRemove);
    void setPeriodofAnounceList(QString anounceSet,QString period);
    QString getPeriodofAnounceList(QString anounceGet);
    /*Application functions*/
private:
    bool m_stateNoFolderFound;
    bool m_stateDispWatchOnVideoArea;
    bool m_stateDispTextOnStationArea;
    bool m_stateSpecialAnounceActive;
    bool m_stateRegularAnounceActive;
    bool m_stateNoGpsInfo;
    bool m_stateNoStationInfo;
    QString m_errCode;
    bool m_updateStations;
    bool m_stateNetwork;
    QString m_currentLine;
    QString m_currentStation;
    QString m_currentSpecialAnounce;
    QString m_nextStation;
    bool m_lineSelected;
    bool m_dataImported;
    bool m_folderStructureOK;
    QString m_actualLongitude;
    QString m_actualLatitude;
    bool m_comAppOK;
    unsigned int m_currentStationOrder;
    QString m_stationConfirmed;
    QString m_confirmStationID;
    QString m_vehicleSpeed;
    bool m_anyDoorOpen;
    bool m_updateInProgress;
    QString m_vehicleID;
    bool m_selectionDone;
    QString m_playSound;
    bool m_pauseAnounce;
    QString m_playSoundStations;
    QString m_activeCommercial;
    QString m_activeAnounce;
    unsigned int m_lifeSign;
    bool m_periodicalAnounceAllowed;
};
struct  endPointsClass::station{
    QString id;
    QString name;
    QString latitude;
    QString longitude;
    QString soundURL;
    QString passed;
    bool operator==(const station& other) const {
        return this->id == other.id;
    }
};
struct  endPointsClass::videos{
    QString id;
    QString description;
};


inline endPointsClass::endPointsClass(QObject *parent) : QObject(parent)
{
    ioCom.VehicleID =0;
    ioCom.ActiveAnounce="Aktif Degil";
    ioCom.ActiveCommercial="Aktif Degil";
    ioCom.ActiveLineInfo= "Seçilmedi";
    ioCom.LifeSign=0;
    ioCom.ActiveStation="Yok";
    ioCom.NextStationId=0;
    ioCom.ActiveStationId=0;
    ioCom.NextStation="";
    ioCom.GPSOk=false;
    ioCom.GPSLongtitude=0;
    ioCom.GPSLatitude=0;
    iiCom.VehicleID=0;
    iiCom.LifeSign=0;
    iiCom.VehicleSpeed=0;
    iiCom.AnyDoorOpen=false;
    iiCom.ProgressUpdate=false;

     m_stateNoFolderFound=false;
     m_stateDispWatchOnVideoArea=false;
     m_stateDispTextOnStationArea=false;
     m_stateSpecialAnounceActive=false;
     m_stateRegularAnounceActive=false;
     m_stateNoGpsInfo=false;
     m_stateNoStationInfo=false;
     m_errCode="null";
     m_updateStations=false;
     m_stateNetwork=false;
     m_currentLine="null";
     m_currentStation="null";
     m_currentSpecialAnounce="null";
     m_nextStation="null";
     m_lineSelected=false;
     m_dataImported=false;
     m_folderStructureOK=false;
     m_actualLongitude="null";
     m_actualLatitude="null";
     m_comAppOK=false;
     viewLine="null";
}

inline endPointsClass::~endPointsClass()
{
    for(QList<station*> list : allLineStations){
        for(station *st  : list){
            delete st;
        }
        list.clear();
    }
    allLineStations.clear();
}

inline QList<QString> endPointsClass::getLineList()
{
    QList<QString> lines;
    for(const QString keys : allLineStations.keys()){
        lines.append(keys);
    }
    return lines;
}

inline QList<QString> endPointsClass::getStations()
{
    QList<QString> stations;
    if(allLineStations.contains(this->viewLine))
    for(station*  stationsLine : allLineStations.value(viewLine)){
        stations.append(stationsLine->name);
    }
    return stations;
}

inline void endPointsClass::selectviewLine(QString lineID)
{
    this->viewLine = lineID;
}

inline void endPointsClass::selectLine()/*Called on button pressed at line page "StationSelect.qml"*/
{
    //qDebug()<<"selectLine çağırıldı ";
    setLineSelected(false);
    this->setSelectionDone(false);
    this->selectedLine = this->viewLine;
    currentLineStations.clear();
    for(station * obj  : allLineStations.value( this->selectedLine)){
        currentLineStations.append(*obj);
    }
    setLineSelected(true);
}

inline void endPointsClass::getConfirmationCurrentStation(QString currentStationID)
{   //qDebug()<<"getConfirmationCurrentStation çağırıldı ";
    setConfirmStationID(currentStationID);
    emit confirmPopup();
}

inline QString endPointsClass::getOffsetStation(QString currentStationID, int offset)
{
    int index=0;
    for(station* Obj : this->allLineStations.value(this->selectedLine)){
        if(Obj->id ==currentStationID){
        index = this->allLineStations.value(this->selectedLine).indexOf(Obj);
        }
    }
    if((index + offset < this->allLineStations.value(this->selectedLine).size())&&(index + offset > 0)){
        return this->allLineStations.value(this->selectedLine).at(index+offset)->id;
    }else{
        return currentStationID;
    }
}

inline void endPointsClass::confirmStationSelection(QString currentStationID)
{
        this->setStationConfirmed(currentStationID);
}

inline void endPointsClass::increaseConfirmationStation()
{
    int index=0;
    if(this->allLineStations.contains(this->selectedLine)){
        for(station* Obj : this->allLineStations.value(this->selectedLine)){
            if(Obj->id ==confirmStationID()){
                index = this->allLineStations.value(this->selectedLine).indexOf(Obj);
            }
        }
        if(index+1 < this->allLineStations.value(this->selectedLine).size()){
            setConfirmStationID(this->allLineStations.value(this->selectedLine).at(index+1)->id);
        }

    }
}

inline void endPointsClass::deacreaseConfirmationStation()
{
    int index=0;
    if(this->allLineStations.contains(this->selectedLine)){
        for(station* Obj : this->allLineStations.value(this->selectedLine)){
            if(Obj->id ==confirmStationID()){
                index = this->allLineStations.value(this->selectedLine).indexOf(Obj);
            }
        }
        if(index >0){
            setConfirmStationID(this->allLineStations.value(this->selectedLine).at(index-1)->id);
        }

    }
}

inline QString endPointsClass::getStationName(QString stationID)
{
    for(const QList<station*> Obj1 : this->allLineStations){
        for(station* Obj2 : Obj1){
            if(Obj2->id ==stationID){
                return Obj2->name;
            }
        }
    }
    return stationID;
}

inline void endPointsClass::cancelLineSelection()
{
    this->setLineSelected(false);
    this->setSelectionDone(false);
    this->selectedLine.clear();
    this->setCurrentLine("");
    this->setCurrentStation("");
    this->setNextStation("");
    this->currentViewFour.clear();
}

inline void endPointsClass::logVideoPlay(QString mediaId)
{
    QString text = "";
    for (const videos& video : this->videoList) {
        if(video.id==mediaId){
            text= video.description;
            this->setErrCode(text.remove("\"")+" isimli medya oynatılıyor");
            setActiveCommercial(text.remove("\""));
        }
        //qDebug()<<video.description;
    }
    if(text !=""){
        this->setErrCode(text.remove("\"")+" isimli medya oynatılıyor");
    }else{
         this->setErrCode(mediaId+" dosya isimli medya oynatılıyor, medya bilgisi yer almıyor.");
    }

}

inline void endPointsClass::logMediaPlay(QString mediaName)
{

    if(!mediaName.isEmpty()){
        QString data = mediaName.split("/").last().remove(".mp3");
        this->setErrCode(data+" isimli ses dosyası oynatılıyor.");
        setActiveAnounce(data);
    }else{
        setActiveAnounce("");
    }


}

inline void endPointsClass::setVideoUnavailable()
{
    setStateDispWatchOnVideoArea(true);

}

inline void endPointsClass::setVideoAvailable()
{
    setStateDispWatchOnVideoArea(false);

}

inline QString endPointsClass::getViewFourMember(unsigned int index)
{
    if(index < this->currentViewFour.size()){
         return this->currentViewFour.at(index);
    }
    else{
         return "";
    }
}

inline QString endPointsClass::getPathAudio(QString stationID)
{
    for(endPointsClass::station Obj : this->currentLineStations){
        if(Obj.id == stationID){
            //qDebug()<<"found getPathAudio";
            return Obj.soundURL;
        }
    }
    return "";
}

inline QList<QString> endPointsClass::getAnounceList()
{
    return this->anounceList;
}

inline void endPointsClass::addPeriodicAnounceList(QString anounceAdd)
{
    for(endPointsClass::anounce *member : this->periodicAnounceList){
        if(member->name == anounceAdd){
            member->periodical = true;
        }
    }
}

inline void endPointsClass::removePeriodicAnounceList(QString anounceRemove)
{
    for(endPointsClass::anounce *member : this->periodicAnounceList){
        if(member->name == anounceRemove){
            member->periodical = false;
        }
    }
}

inline void endPointsClass::setPeriodofAnounceList(QString anounceSet, QString period)
{
    for(endPointsClass::anounce *member : this->periodicAnounceList){
        //qDebug()<<member->name;
        if(member->name == anounceSet){
            member->period = period;
            //qDebug()<<period;
        }
    }
}

inline QString endPointsClass::getPeriodofAnounceList(QString anounceGet)
{
    for(endPointsClass::anounce *member : this->periodicAnounceList){
        if(member->name == anounceGet){
            return member->period;
        }
    }
    return "Ayarlanmadı";
}

inline bool endPointsClass::stateNoFolderFound() const
{
    return m_stateNoFolderFound;
}

inline void endPointsClass::setStateNoFolderFound(bool newStateNoFolderFound)
{
    if (m_stateNoFolderFound == newStateNoFolderFound)
        return;
    m_stateNoFolderFound = newStateNoFolderFound;
    emit stateNoFolderFoundChanged();
}

inline bool endPointsClass::stateDispWatchOnVideoArea() const
{
    return m_stateDispWatchOnVideoArea;
}

inline void endPointsClass::setStateDispWatchOnVideoArea(bool newStateDispWatchOnVideoArea)
{
    if (m_stateDispWatchOnVideoArea && !newStateDispWatchOnVideoArea){
        this->setErrCode("Medya gösterimi mümkün. Ekran koruyucu kapatılıyor.");
    }
    if (m_stateDispWatchOnVideoArea && !newStateDispWatchOnVideoArea){
        this->setErrCode("Medya gösterimi mümkün değil. Ekran koruyucu açılıyor.");
    }
    if (m_stateDispWatchOnVideoArea == newStateDispWatchOnVideoArea)
        return;
    m_stateDispWatchOnVideoArea = newStateDispWatchOnVideoArea;
    emit stateDispWatchOnVideoAreaChanged();
}

inline bool endPointsClass::stateDispTextOnStationArea() const
{
    return m_stateDispTextOnStationArea;
}

inline void endPointsClass::setStateDispTextOnStationArea(bool newStateDispTextOnStationArea)
{
    if (m_stateDispTextOnStationArea == newStateDispTextOnStationArea)
        return;
    m_stateDispTextOnStationArea = newStateDispTextOnStationArea;
    emit stateDispTextOnStationAreaChanged();
}

inline bool endPointsClass::stateSpecialAnounceActive() const
{
    return m_stateSpecialAnounceActive;
}

inline void endPointsClass::setStateSpecialAnounceActive(bool newStateSpecialAnounceActive)
{
    if (m_stateSpecialAnounceActive == newStateSpecialAnounceActive)
        return;
    m_stateSpecialAnounceActive = newStateSpecialAnounceActive;
    emit stateSpecialAnounceActiveChanged();
}

inline bool endPointsClass::stateRegularAnounceActive() const
{
    return m_stateRegularAnounceActive;
}

inline void endPointsClass::setStateRegularAnounceActive(bool newStateRegularAnounceActive)
{
    if (m_stateRegularAnounceActive == newStateRegularAnounceActive)
        return;
    m_stateRegularAnounceActive = newStateRegularAnounceActive;
    emit stateRegularAnounceActiveChanged();
}

inline bool endPointsClass::stateNoGpsInfo() const
{
    return m_stateNoGpsInfo;
}

inline void endPointsClass::setStateNoGpsInfo(bool newStateNoGpsInfo)
{
    if (m_stateNoGpsInfo == newStateNoGpsInfo)
        return;
    m_stateNoGpsInfo = newStateNoGpsInfo;
    emit stateNoGpsInfoChanged();
}

inline bool endPointsClass::stateNoStationInfo() const
{
    return m_stateNoStationInfo;
}

inline void endPointsClass::setStateNoStationInfo(bool newStateNoStationInfo)
{
    if (m_stateNoStationInfo == newStateNoStationInfo)
        return;
    m_stateNoStationInfo = newStateNoStationInfo;
    emit stateNoStationInfoChanged();
}


inline QString endPointsClass::errCode() const
{
    return m_errCode;
}

inline void endPointsClass::setErrCode(const QString &newErrCode)
{
    if (m_errCode == newErrCode)
        return;
    m_errCode = newErrCode;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    errList.append("["+formattedDateTime+"]"+m_errCode);
    emit errCodeChanged();
}




inline bool endPointsClass::updateStations() const
{
    return m_updateStations;
}

inline void endPointsClass::setUpdateStations(bool newUpdateStations)
{
    if (m_updateStations == newUpdateStations)
        return;
    m_updateStations = newUpdateStations;
    emit updateStationsChanged();
}

inline bool endPointsClass::stateNetwork() const
{
    return m_stateNetwork;
}

inline void endPointsClass::setStateNetwork(bool newStateNetwork)
{
    if (m_stateNetwork == newStateNetwork)
        return;
    m_stateNetwork = newStateNetwork;    
    emit stateNetworkChanged();
}

inline QString endPointsClass::currentLine() const
{
    return m_currentLine;
}

inline void endPointsClass::setCurrentLine(const QString &newCurrentLine)
{
    if (m_currentLine == newCurrentLine)
        return;
    m_currentLine = newCurrentLine;
    emit currentLineChanged();
}

inline QString endPointsClass::currentStation() const
{
    return m_currentStation;
}

inline void endPointsClass::setCurrentStation(const QString &newCurrentStation)
{
    if (m_currentStation == newCurrentStation)
        return;
    m_currentStation = newCurrentStation;
    emit currentStationChanged();
}

inline QString endPointsClass::currentSpecialAnounce() const
{
    return m_currentSpecialAnounce;
}

inline void endPointsClass::setCurrentSpecialAnounce(const QString &newCurrentSpecialAnounce)
{
    if (m_currentSpecialAnounce == newCurrentSpecialAnounce)
        return;
    m_currentSpecialAnounce = newCurrentSpecialAnounce;
    emit currentSpecialAnounceChanged();
}

inline QString endPointsClass::nextStation() const
{
    return m_nextStation;
}


inline void endPointsClass::setNextStation(const QString &newNextStation)
{
    if (m_nextStation == newNextStation)
        return;
    m_nextStation = newNextStation;
    emit nextStationChanged();
}

inline bool endPointsClass::lineSelected() const
{
    return m_lineSelected;
}

inline void endPointsClass::setLineSelected(bool newLineSelected)
{
    if (m_lineSelected == newLineSelected)
        return;
    m_lineSelected = newLineSelected;
    emit lineSelectedChanged();
}

inline bool endPointsClass::dataImported() const
{
    return m_dataImported;
}

inline void endPointsClass::setDataImported(bool newDataImported)
{
    m_dataImported = newDataImported;
    emit dataImportedChanged();
}

inline bool endPointsClass::folderStructureOK() const
{
    return m_folderStructureOK;
}

inline void endPointsClass::setFolderStructureOK(bool newFolderStructureOK)
{
    if (m_folderStructureOK == newFolderStructureOK)
        return;
    m_folderStructureOK = newFolderStructureOK;
    emit folderStructureOKChanged();
}

inline void endPointsClass::addItemStations(QString ID, QString dir, QList<station *> stationAdd)
{
    if(allLineStations.contains(ID+"_"+dir)){
        allLineStations[ID+dir].clear();
        allLineStations[ID+dir].append(stationAdd);
    }else{
        allLineStations.insert(ID+"_"+dir,stationAdd);
    }
}

inline QString endPointsClass::actualLongitude() const
{
    return m_actualLongitude;
}

inline void endPointsClass::setactualLongitude(const QString &newactualLongitude)
{
    if (m_actualLongitude == newactualLongitude)
        return;
    m_actualLongitude = newactualLongitude;
    emit actualLongitudeChanged();
}

inline QString endPointsClass::actualLatitude() const
{
    return m_actualLatitude;
}

inline void endPointsClass::setactualLatitude(const QString &newactualLatitude)
{
    if (m_actualLatitude == newactualLatitude)
        return;
    m_actualLatitude = newactualLatitude;
    emit actualLatitudeChanged();
}

inline bool endPointsClass::comAppOK() const
{
    return m_comAppOK;
}

inline void endPointsClass::setComAppOK(bool newComAppOK)
{
    if (m_comAppOK == newComAppOK)
        return;
    m_comAppOK = newComAppOK;
    emit comAppOKChanged();
}


inline unsigned int endPointsClass::currentStationOrder() const
{
    return m_currentStationOrder;
}

inline void endPointsClass::setCurrentStationOrder(unsigned int newcurrentStationOrder)
{
    if (m_currentStationOrder == newcurrentStationOrder)
        return;
    m_currentStationOrder = newcurrentStationOrder;
    emit currentStationOrderChanged();
}

inline QString endPointsClass::stationConfirmed() const
{
    return m_stationConfirmed;
}

inline void endPointsClass::setStationConfirmed(const QString &newStationConfirmed)
{
    if (m_stationConfirmed == newStationConfirmed)
        return;
    m_stationConfirmed = newStationConfirmed;
    emit StationConfirmedChanged();
}


inline QString endPointsClass::confirmStationID() const
{
    return m_confirmStationID;
}

inline void endPointsClass::setConfirmStationID(const QString &newConfirmStationID)
{
    if (m_confirmStationID == newConfirmStationID)
        return;
    m_confirmStationID = newConfirmStationID;
    emit confirmStationIDChanged();
}



inline QString endPointsClass::vehicleSpeed() const
{
    return m_vehicleSpeed;
}

inline void endPointsClass::setVehicleSpeed(const QString &newVehicleSpeed)
{
    if (m_vehicleSpeed == newVehicleSpeed)
        return;
    m_vehicleSpeed = newVehicleSpeed;
    emit vehicleSpeedChanged();
}

inline bool endPointsClass::anyDoorOpen() const
{
    return m_anyDoorOpen;
}

inline void endPointsClass::setAnyDoorOpen(bool newAnyDoorOpen)
{
    if (m_anyDoorOpen == newAnyDoorOpen)
        return;
    m_anyDoorOpen = newAnyDoorOpen;
    emit anyDoorOpenChanged();
}

inline bool endPointsClass::updateInProgress() const
{
    return m_updateInProgress;
}

inline void endPointsClass::setUpdateInProgress(bool newUpdateInProgress)
{
    if (m_updateInProgress == newUpdateInProgress)
        return;
    m_updateInProgress = newUpdateInProgress;
    emit updateInProgressChanged();
}

inline QString endPointsClass::vehicleID() const
{
    return m_vehicleID;
}

inline void endPointsClass::setVehicleID(const QString &newVehicleID)
{
    if (m_vehicleID == newVehicleID)
        return;
    m_vehicleID = newVehicleID;
    emit vehicleIDChanged();
}

inline bool endPointsClass::selectionDone() const
{
    return m_selectionDone;
}

inline void endPointsClass::setSelectionDone(bool newSelectionDone)
{
    if (m_selectionDone == newSelectionDone)
        return;
    m_selectionDone = newSelectionDone;
    emit selectionDoneChanged();
}

inline QString endPointsClass::playSound() const
{
    return m_playSound;
}

inline void endPointsClass::setPlaySound(const QString &newPlaySound)
{
    m_playSound = newPlaySound;
    emit playSoundChanged();
}


inline bool endPointsClass::pauseAnounce() const
{
    return m_pauseAnounce;
}

inline void endPointsClass::setPauseAnounce(bool newPauseAnounce)
{
    if (m_pauseAnounce == newPauseAnounce)
        return;
    m_pauseAnounce = newPauseAnounce;
    emit pauseAnounceChanged();
}


inline QString endPointsClass::playSoundStations() const
{
    return m_playSoundStations;
}

inline void endPointsClass::setPlaySoundStations(const QString &newPlaySoundStations)
{
    m_playSoundStations = newPlaySoundStations ;
    emit playSoundStationsChanged();
}

inline void endPointsClass::clearList()
{
    QMap<QString, QList<station*>>::iterator it = allLineStations.begin();
    while (it != allLineStations.end()) {
        // Her bir QList içindeki elemanları sil
        QList<station*> &stations = it.value();
        qDeleteAll(stations);
        stations.clear();
        // QMap içindeki anahtar-değer çiftini sil
        it = allLineStations.erase(it);
    }
    this->viewLine.clear();
    this->currentViewFour.clear();
    ioCom.VehicleID =0;
    ioCom.ActiveAnounce="Aktif Degil";
    ioCom.ActiveCommercial="Aktif Degil";
    ioCom.ActiveLineInfo= "Seçilmedi";
    ioCom.LifeSign=0;
    ioCom.ActiveStation="Yok";
    ioCom.NextStationId=0;
    ioCom.ActiveStationId=0;
    ioCom.NextStation="";
    iiCom.VehicleID=0;
    iiCom.LifeSign=0;
    ioCom.GPSOk=false;
    ioCom.GPSLongtitude=0;
    ioCom.GPSLatitude=0;
    iiCom.VehicleSpeed=0;
    iiCom.AnyDoorOpen=false;
    iiCom.ProgressUpdate=false;

    m_stateNoFolderFound=false;
    m_stateDispWatchOnVideoArea=false;
    m_stateDispTextOnStationArea=false;
    m_stateSpecialAnounceActive=false;
    m_stateRegularAnounceActive=false;
    m_stateNoGpsInfo=false;
    m_stateNoStationInfo=false;
    m_errCode="null";
    m_updateStations=false;
    m_stateNetwork=false;
    m_currentLine="null";
    m_currentStation="null";
    m_currentSpecialAnounce="null";
    m_nextStation="null";
    m_lineSelected=false;
    m_dataImported=false;
    m_folderStructureOK=false;
    m_actualLongitude="null";
    m_actualLatitude="null";
    m_comAppOK=false;
    viewLine="null";
}


inline QString endPointsClass::activeCommercial() const
{
    return m_activeCommercial;
}

inline void endPointsClass::setActiveCommercial(const QString &newActiveCommercial)
{
    if (m_activeCommercial == newActiveCommercial)
        return;
    m_activeCommercial = newActiveCommercial;
    emit activeCommercialChanged();
}

inline QString endPointsClass::activeAnounce() const
{
    return m_activeAnounce;
}

inline void endPointsClass::setActiveAnounce(const QString &newActiveAnounce)
{
    if (m_activeAnounce == newActiveAnounce)
        return;
    m_activeAnounce = newActiveAnounce;
    emit activeAnounceChanged();
}


inline unsigned int endPointsClass::lifeSign() const
{
    return m_lifeSign;
}

inline void endPointsClass::setLifeSign(unsigned int newLifeSign)
{
    if (m_lifeSign == newLifeSign)
        return;
    m_lifeSign = newLifeSign;
    emit lifeSignChanged();
}



inline bool endPointsClass::periodicalAnounceAllowed() const
{
    return m_periodicalAnounceAllowed;
}

inline void endPointsClass::setPeriodicalAnounceAllowed(bool newPeriodicalAnounceAllowed)
{
    if (m_periodicalAnounceAllowed == newPeriodicalAnounceAllowed)
        return;
    m_periodicalAnounceAllowed = newPeriodicalAnounceAllowed;
    emit periodicalAnounceAllowedChanged();
}
#endif // ENDPOINTSCLASS_H
