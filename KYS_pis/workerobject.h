
#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H


#include <QObject>
#include "endPointsClass.h"
#include <QTimer>
class workerObject : public QObject
{
    Q_OBJECT

private:
    endPointsClass *endPoints;
    QTimer *timerOneSec;

public:
    explicit workerObject(QObject *parent = nullptr, endPointsClass *endPoints = nullptr);
    ~workerObject();
public slots:

    void startObject();
    void stopObject();

    void sendHttpReq();
    void readJSON();
    void readStationLIST();
    void readApptoPis();

    void writePistoApp();

signals:

    void httpReqDone();
    void JSONDone();
    void readJson();
};

#endif // WORKEROBJECT_H
