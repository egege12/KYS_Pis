
#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H


#include <QObject>
#include "endPointsClass.h"

class workerObject : public QObject
{
    Q_OBJECT

private:
    endPointsClass *endPoints;
public:
    explicit workerObject(QObject *parent = nullptr, endPointsClass *endPoints = nullptr);

public slots:

    void startObject();
    void stopObject();

signals:

};

#endif // WORKEROBJECT_H
