
#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H


#include <QObject>
#include "endPointsClass.h"
#include <QTimer>
#include <QList>

class workerObject : public QObject
{
    Q_OBJECT

private:
    endPointsClass *endPoints;
    QTimer *timer1;
    QTimer *timer2;
    QList<QString> lines;
public:
    explicit workerObject(QObject *parent = nullptr, endPointsClass *endPoints = nullptr);
    ~workerObject();

    bool checkConnection();
    bool checkFolderStations();
    bool checkFolderVideo();
    bool checkFolderAudioForLines();
    bool checkFolderSpecialAnouncement();
    //If one fails cycle check starts for that
    bool enableCycleCheckFileLines();
    bool enableCycleCheckJson();
    bool enableCycleCheckVideos();
    bool enableCycleConnectionCheck();
    bool enableCycleAuidoCheck();

    bool linesOK;
    bool stationsOK;
    bool GPSOK;
    bool audio

public slots:

    void startObject();
    void stopObject();

    void sendHttpReq();
    void readJSON();
    void readLineLIST();
    void rwComApp();

    void cycleCall();



signals:

    void doneReqHTTP();
    void doneReadJSON(bool state);
    void donereadLineList();

};

#endif // WORKEROBJECT_H
