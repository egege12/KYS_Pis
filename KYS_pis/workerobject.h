
#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H


#include <QObject>


class workerObject : public QObject
{
    Q_OBJECT
public:
    explicit workerObject(QObject *parent = nullptr);

signals:

};

#endif // WORKEROBJECT_H
