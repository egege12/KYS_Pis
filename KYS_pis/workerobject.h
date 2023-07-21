
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
    unsigned failCounterLifeSign;
    unsigned failGPSCounter;

    //Old containers
    double GPSLatitude;
    double GPSLongtitude;
public:
    explicit workerObject(QObject *parent = nullptr, endPointsClass *endPoints = nullptr);
    ~workerObject();




    //Helpers
    void compareAndCopyFile(const QString& sourcePath, const QString& destinationPath);
    void saveLogs();
    //Operations
    void readStations();
    void sendHttpReq();
    bool readJSON(bool useBackup);
    bool readLineLIST(bool useBackup);
    void saveDataStations(const QJsonArray& dataStations);

    //Checkers
    bool checkConnection();
    bool checkService();
    void checkLifeSign(unsigned oldLifeSign, unsigned newLifeSign);
    bool checkGPS();
    bool checkFolderStations();
    bool checkFolderVideo();
    bool checkFolderAudioForLines();
    bool checkFolderSpecialAnouncement();
    bool checkFileLines();
    bool checkFileJson();


    //If one fails cycle check starts for that
    void enableCycleCheckUpdate(bool cycleCheckUpdate);
    void enableCycleCheckRead(bool cycleCheckRead);
    bool cycleCheckUpdate;
    bool cycleCheckRead;

    bool processBlockedConnection;
    bool processBlockedFileLines;
    bool processBlockedService;





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
