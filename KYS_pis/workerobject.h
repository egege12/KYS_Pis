
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

    //Helpers
    void compareAndCopyFile(const QString& sourcePath, const QString& destinationPath);

    //Operations
    void readStations();
    void sendHttpReq();
    bool readJSON(bool useBackup);
    bool readLineLIST(bool useBackup);
    void saveDataStations(const QJsonArray& dataStations);
    bool checkConnection();
    bool checkService();

    //If one fails cycle check starts for that
    void enableCycleCheckFileLines(bool cycleCheckFileLines);
    void enableCycleCheckJson(bool cycleCheckJson);
    void enableCycleCheckVideos(bool cycleCheckVideos);
    void enableCycleConnectionCheck(bool cycleCheckConnection);
    void enableCycleAuidoCheck(bool cycleCheckAuido);

    bool linesOK;
    bool stationsOK;
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
    void rwComApp();
    void cycleCall();
    void updateList();

signals:
    void doneUpdate(bool updateStations);


};

#endif // WORKEROBJECT_H
