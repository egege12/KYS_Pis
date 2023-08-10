
#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H


#include <QObject>
#include "endPointsClass.h"
#include "qfilesystemwatcher.h"
#include <QTimer>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QLocalSocket>
#include <QLocalServer>
class workerObject : public QObject
{
    Q_OBJECT

private:
    endPointsClass *endPoints;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    QTimer *timer5;
    QList<QString> lines;
    QList<QString> pendingAnonunceList;
    unsigned failCounterLifeSign;
    unsigned failGPSCounter;
    QSerialPort *serialPort;
    bool serialPortFailed;
    bool GPSGNSSNotEmpty;
    QByteArray receivedData;
    QFileSystemWatcher *watcherVideoFolder;
    QFileSystemWatcher *watcherAnounceFolder;
    bool receivedDataGNGGAFlag;
    //Old containers
    double GPSLatitude;
    double GPSLongtitude;
    //Application members
    bool inStation;
    bool busStopped;
    bool waitToStop;
    QLocalSocket *comPisAppSocket;
    QLocalServer *comPisServer;
    //Application Methods

    void beginSpecificStation(QString stationID);
public:
    explicit workerObject(QObject *parent = nullptr, endPointsClass *endPoints = nullptr);
    ~workerObject();
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    void mainPIS();


    //Helpers
    void compareAndCopyFile(const QString& sourcePath, const QString& destinationPath);
    void saveLogs();
    void deleteOldestFiles(QString folderPath);    //Operations
    void readStations();
    void sendHttpReq();
    bool readJSON(bool useBackup);
    bool readLineLIST(bool useBackup);
    void saveDataStations(const QJsonArray& dataStations);
    void gnggaSplitter(QByteArray &line);

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
    void checkAudioFolder();

    //If one fails cycle check starts for that
    /*CYCLE OPERATIONS*/void enableCycleCheckUpdate(bool cycleCheckUpdate);
    /*CYCLE OPERATIONS*/void enableCycleCheckRead(bool cycleCheckRead);
    /*CYCLE OPERATIONS*/bool cycleCheckUpdate;
    /*CYCLE OPERATIONS*/bool cycleCheckRead;

    /*CYCLE OPERATIONS*/bool processBlockedConnection;
    /*CYCLE OPERATIONS*/bool processBlockedFileLines;
    /*CYCLE OPERATIONS*/bool processBlockedService;



public slots:
    void readVideoFolder();
    void readAnounceFolder();
    void startObject();
    void stopObject();
    //void rwComApp();
    void cycleCall();
    void updateList();
    void handleLineSelection();
    void confirmLineSelection();
    void readSerialGPS();
    void onTimeoutGPS();
    void onAnounceControl();
    void rwComSocketData_new();
    void onTimeOutSocket();

    void handleConnection();
    void clientDisconnected();
signals:
    void doneUpdate(bool updateStations);


};



#endif // WORKEROBJECT_H
