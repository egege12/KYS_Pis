
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


    bool checkFolderStations();
    bool checkFileLines();
    bool checkFileJson();
    bool checkFolderVideo();
    bool checkFolderAudioForLines();
    bool checkFolderSpecialAnouncement();
    //If one fails cycle check starts for that
    void enableCycleCheckFileLines(bool cycleCheckFileLines);
    void enableCycleCheckJson(bool cycleCheckJson);
    void enableCycleCheckVideos(bool cycleCheckVideos);
    void enableCycleConnectionCheck(bool cycleCheckConnection);
    void enableCycleAuidoCheck(bool cycleCheckAuido);

    bool linesOK;
    bool stationsOK;
    bool JSONOK;
    bool JSONReadOK;
    bool GPSOK;
    bool audioOK;

    bool cycleCheckFileLines;
    bool cycleCheckJson;
    bool cycleCheckVideos;
    bool cycleCheckConnection;
    bool cycleCheckAuido;

public slots:

    void startObject();
    void stopObject();

    void sendHttpReq();
    void readJSON();
    void readLineLIST();
    void rwComApp();

    void cycleCall();

    void saveDataStations(const QJsonArray& dataStations);

    bool checkConnection();
    bool check

signals:
    void doneConnectionCheck();
    void doneServiceCheck();
    void doneReqHTTP();
    void doneReadJSON(bool state);
    void donereadLineList();


};

#endif // WORKEROBJECT_H
