#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QQmlContext>
#include "workerobject.h"


int main(int argc, char *argv[])
{
    //Thread spread
    QThread workerThread;
    endPointsClass *const endPoints = new endPointsClass;
    QThread::currentThread()->setObjectName("Main Thread");
    workerThread.setObjectName("Backend Thread");

    workerObject serviceObj(nullptr,endPoints);
    serviceObj.moveToThread(&workerThread);

    QObject::connect(&workerThread, SIGNAL(started()), &serviceObj, SLOT(startObject()));
    QObject::connect(&workerThread, SIGNAL(finished()), &serviceObj, SLOT(stopObject()));
    workerThread.start();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Birinci QML dosyası ekleme
    const QUrl url("qrc:/Main.qml");


    //End point class definition should be done before engine load but initilized
    QQmlContext * Context1 = engine.rootContext();
    Context1->setContextProperty("endPoints", endPoints);

    engine.load(url);

    return app.exec();
}

