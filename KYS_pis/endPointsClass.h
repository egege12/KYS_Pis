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

    Q_PROPERTY(bool stateNoInit READ stateNoInit WRITE setStateNoInit NOTIFY stateNoInitChanged)
    Q_PROPERTY(bool stateDispWatchOnVideoArea READ stateDispWatchOnVideoArea WRITE setStateDispWatchOnVideoArea NOTIFY stateDispWatchOnVideoAreaChanged)
    Q_PROPERTY(bool stateDispTextOnStationArea READ stateDispTextOnStationArea WRITE setStateDispTextOnStationArea NOTIFY stateDispTextOnStationAreaChanged)

    Q_PROPERTY(bool stateNoGpsInfo READ stateNoGpsInfo WRITE setStateNoGpsInfo NOTIFY stateNoGpsInfoChanged)
    Q_PROPERTY(bool stateNoStationInfo READ stateNoStationInfo WRITE setStateNoStationInfo NOTIFY stateNoStationInfoChanged)
    Q_PROPERTY(bool stateUpdating READ stateUpdating WRITE setStateUpdating NOTIFY stateUpdatingChanged)
    Q_PROPERTY(bool stateNetwork READ stateNetwork WRITE setStateNetwork NOTIFY stateNetworkChanged)
    Q_PROPERTY(QString errCode READ errCode WRITE setErrCode NOTIFY errCodeChanged)

    Q_PROPERTY(bool dataImported READ dataImported WRITE setDataImported NOTIFY dataImportedChanged)
    Q_PROPERTY(bool folderStructureOK READ folderStructureOK WRITE setFolderStructureOK NOTIFY folderStructureOKChanged)
    Q_PROPERTY(bool updateStations READ updateStations WRITE setUpdateStations NOTIFY updateStationsChanged)
    Q_PROPERTY(bool updatingStations READ updatingStations WRITE setUpdatingStations NOTIFY updatingStationsChanged)
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
    Q_PROPERTY(bool stateSpecialAnounceActive READ stateSpecialAnounceActive WRITE setStateSpecialAnounceActive NOTIFY stateSpecialAnounceActiveChanged)
    Q_PROPERTY(bool stateRegularAnounceActive READ stateRegularAnounceActive WRITE setStateRegularAnounceActive NOTIFY stateRegularAnounceActiveChanged)


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

    QList<QString> errList{0};
    QMap<QString,QList<station*>> allLineStations;
    QList<station> currentLineStations;
    explicit endPointsClass(QObject *parent = nullptr);
    ~endPointsClass();
    bool stateNoInit() const;
    void setStateNoInit(bool newStateNoInit);

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

    bool stateUpdating() const;
    void setStateUpdating(bool newStateUpdating);

    QString errCode() const;
    void setErrCode(const QString &newErrCode);

    bool updateStations() const;
    void setUpdateStations(bool newUpdateStations);

    bool updatingStations() const;
    void setUpdatingStations(bool newUpdatingStations);

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

    void selectLine(QString ID,QString dir,QList<station*>);

    QString actualLongitude() const;
    void setactualLongitude(const QString &newactualLongitude);

    QString actualLatitude() const;
    void setactualLatitude(const QString &newactualLatitude);

    bool comAppOK() const;
    void setComAppOK(bool newComAppOK);

signals:
    void stateNoInitChanged();

    void stateNoFolderFoundChanged();

    void stateDispWatchOnVideoAreaChanged();

    void stateDispTextOnStationAreaChanged();

    void stateSpecialAnounceActiveChanged();

    void stateRegularAnounceActiveChanged();

    void stateNoGpsInfoChanged();

    void stateNoStationInfoChanged();

    void stateUpdatingChanged();

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

private:
    bool m_stateNoInit;
    bool m_stateNoFolderFound;
    bool m_stateDispWatchOnVideoArea;
    bool m_stateDispTextOnStationArea;
    bool m_stateSpecialAnounceActive;
    bool m_stateRegularAnounceActive;
    bool m_stateNoGpsInfo;
    bool m_stateNoStationInfo;
    bool m_stateUpdating;
    QString m_errCode;
    bool m_updateStations;
    bool m_updatingStations;
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
};
struct  endPointsClass::station{
    QString id;
    QString name;
    QString latitude;
    QString longitude;
    QString soundOK;
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

inline bool endPointsClass::stateNoInit() const
{
    return m_stateNoInit;
}

inline void endPointsClass::setStateNoInit(bool newStateNoInit)
{
    if (m_stateNoInit == newStateNoInit)
        return;
    m_stateNoInit = newStateNoInit;
    emit stateNoInitChanged();
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

inline bool endPointsClass::stateUpdating() const
{
    return m_stateUpdating;
}

inline void endPointsClass::setStateUpdating(bool newStateUpdating)
{
    if (m_stateUpdating == newStateUpdating)
        return;
    m_stateUpdating = newStateUpdating;
    emit stateUpdatingChanged();
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

inline bool endPointsClass::updatingStations() const
{
    return m_updatingStations;
}

inline void endPointsClass::setUpdatingStations(bool newUpdatingStations)
{
    if (m_updatingStations == newUpdatingStations)
        return;
    m_updatingStations = newUpdatingStations;
    emit updatingStationsChanged();
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
    if(!m_stateNetwork){
        setErrCode("İnternet bağlantısı kesildi");
    }else
        setErrCode("İnternet bağlantısı sağlandı");
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

inline void endPointsClass::selectLine(QString ID, QString dir, QList<station*>)
{

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
#endif // ENDPOINTSCLASS_H
