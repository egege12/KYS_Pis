//this class is created to use communication between interface and backend

#ifndef ENDPOINTSCLASS_H
#define ENDPOINTSCLASS_H

#include "qobject.h"
#include <QFile>
#include <QList>
#include <QDateTime>
#include <QMap>



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
    Q_PROPERTY(QString currentLine READ currentLine WRITE setCurrentLine NOTIFY currentLineChanged)
    Q_PROPERTY(QString currentDirection READ currentDirection WRITE setCurrentDirection NOTIFY currentDirectionChanged)
    Q_PROPERTY(QString currentStation READ currentStation WRITE setCurrentStation NOTIFY currentStationChanged)
    Q_PROPERTY(QString nextStation READ nextStation WRITE setNextStation NOTIFY nextStationChanged)
    Q_PROPERTY(QString actualLongitude READ actualLongitude WRITE setactualLongitude NOTIFY actualLongitudeChanged)
    Q_PROPERTY(QString actualLatitude READ actualLatitude WRITE setactualLatitude NOTIFY actualLatitudeChanged)
    Q_PROPERTY(QString currentSpecialAnounce READ currentSpecialAnounce WRITE setCurrentSpecialAnounce NOTIFY currentSpecialAnounceChanged)
    Q_PROPERTY(unsigned currentStationOrder READ currentStationOrder WRITE setCurrentStationOrder NOTIFY currentStationOrderChanged)
    Q_PROPERTY(bool stateSpecialAnounceActive READ stateSpecialAnounceActive WRITE setStateSpecialAnounceActive NOTIFY stateSpecialAnounceActiveChanged)
    Q_PROPERTY(bool stateRegularAnounceActive READ stateRegularAnounceActive WRITE setStateRegularAnounceActive NOTIFY stateRegularAnounceActiveChanged)
    Q_PROPERTY(QString stationConfirmed READ stationConfirmed WRITE setStationConfirmed NOTIFY StationConfirmedChanged)
    Q_PROPERTY(QString confirmStationID READ confirmStationID WRITE setConfirmStationID NOTIFY confirmStationIDChanged)
public:
    struct IIData{
        unsigned VehicleID;
        unsigned LifeSign;
        bool GPSOk;
        double GPSLongtitude;
        double GPSLatitude;
        unsigned VehicleSpeed;
        bool AnyDoorOpen;
        bool ProgressUpdate;
    };

    struct IOData{
        unsigned LifeSign;
        unsigned VehicleID;
        unsigned ActiveLineInfo;
        unsigned ActiveDirection;
        QString ActiveStation;
        unsigned ActiveStationId;
        QString NextStation;
        unsigned NextStationId;
        QString ActiveAnounce;
        QString ActiveCommercial;
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

    QString currentDirection() const;
    void setCurrentDirection(const QString &newCurrentDirection);

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

    void currentDirectionChanged();

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

    void anonuceNextStation();

    void updateViewFour();

    void confirmPopup();

    void currentStationOrderChanged();

    void StationConfirmedChanged();

    void confirmStationIDChanged();

    void confirmationIDChanged();

    void videoFolderUpdated();

public slots:
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

    /*Video*/
    void logVideoPlay(QString mediaId);


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
    QString m_currentDirection;
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
};
struct  endPointsClass::station{
    QString id;
    QString name;
    QString latitude;
    QString longitude;
    QString soundOK;
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
    ioCom.ActiveLineInfo= 0;
    ioCom.LifeSign=0;
    ioCom.ActiveStation="Yok";
    ioCom.NextStationId=0;
    ioCom.ActiveStationId=0;
    ioCom.ActiveDirection=0;
    ioCom.NextStation="";
    iiCom.VehicleID=0;
    iiCom.LifeSign=0;
    iiCom.GPSOk=false;
    iiCom.GPSLongtitude=0;
    iiCom.GPSLatitude=0;
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
     m_currentDirection="null";
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
    this->selectedLine = this->viewLine;
    currentLineStations.clear();
    for(station * obj  : allLineStations.value( this->selectedLine)){
        currentLineStations.append(*obj);
    }
    setLineSelected(true);
}

inline void endPointsClass::getConfirmationCurrentStation(QString currentStationID)
{
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
        if(index<this->allLineStations.value(this->selectedLine).size()){
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

inline void endPointsClass::logVideoPlay(QString mediaId)
{
    for (const videos& video : this->videoList) {
        if(video.id==mediaId){
            this->setErrCode(video.description+" isimli medya oynatılıyor");
        }
    }

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

inline QString endPointsClass::currentDirection() const
{
    return m_currentDirection;
}

inline void endPointsClass::setCurrentDirection(const QString &newCurrentDirection)
{
    if (m_currentDirection == newCurrentDirection)
        return;
    m_currentDirection = newCurrentDirection;
    emit currentDirectionChanged();
}

inline QString endPointsClass::nextStation() const
{
    return m_nextStation;
}

inline void endPointsClass::setnextStation(const QString &newNextStation)
{
    if (m_nextStation == newNextStation)
        return;
    m_nextStation = newNextStation;
    emit nextStationChanged();
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
    if (m_dataImported == newDataImported)
        return;
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


#endif // ENDPOINTSCLASS_H
