//this class is created to use communication between interface and backend

#ifndef ENDPOINTSCLASS_H
#define ENDPOINTSCLASS_H

#include "qobject.h"
#include <QFile>
#include <QList>
#include <QDateTime>

class endPointsClass: public QObject{

    Q_OBJECT

    Q_PROPERTY(bool stateNoInit READ stateNoInit WRITE setStateNoInit NOTIFY stateNoInitChanged)
    Q_PROPERTY(bool stateNoFolderFound READ stateNoFolderFound WRITE setStateNoFolderFound NOTIFY stateNoFolderFoundChanged)
    Q_PROPERTY(bool stateDispWatchOnVideoArea READ stateDispWatchOnVideoArea WRITE setStateDispWatchOnVideoArea NOTIFY stateDispWatchOnVideoAreaChanged)
    Q_PROPERTY(bool stateDispTextOnStationArea READ stateDispTextOnStationArea WRITE setStateDispTextOnStationArea NOTIFY stateDispTextOnStationAreaChanged)
    Q_PROPERTY(bool stateSpecialAnounceActive READ stateSpecialAnounceActive WRITE setStateSpecialAnounceActive NOTIFY stateSpecialAnounceActiveChanged)
    Q_PROPERTY(bool stateRegularAnounceActive READ stateRegularAnounceActive WRITE setStateRegularAnounceActive NOTIFY stateRegularAnounceActiveChanged)
    Q_PROPERTY(bool stateNoGpsInfo READ stateNoGpsInfo WRITE setStateNoGpsInfo NOTIFY stateNoGpsInfoChanged)
    Q_PROPERTY(bool stateNoStationInfo READ stateNoStationInfo WRITE setStateNoStationInfo NOTIFY stateNoStationInfoChanged)
    Q_PROPERTY(bool stateUpdating READ stateUpdating WRITE setStateUpdating NOTIFY stateUpdatingChanged)
    Q_PROPERTY(QString errCode READ errCode WRITE setErrCode NOTIFY errCodeChanged)

    QList<QString> errList{0};

public:
    endPointsClass(QObject *parent = nullptr);

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
    void seterrCode(const QString &newErrCode);

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
};

#endif // ENDPOINTSCLASS_H

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

inline void endPointsClass::seterrCode(const QString &newErrCode)
{
    if (m_errCode == newErrCode)
        return;
    m_errCode = newErrCode;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    errList.append("["+formattedDateTime+"]"+m_errCode);
    emit errCodeChanged();
}

inline endPointsClass::endPointsClass(QObject *parent) : QObject(parent)
{

}
