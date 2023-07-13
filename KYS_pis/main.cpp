#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QQmlContext>
#include "workerobject.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //Thread spread
    QThread workerThread;
    endPointsClass *const endPoints = new endPointsClass;
    QThread::currentThread()->setObjectName("Main Thread");
    workerThread.setObjectName("Backend Thread");

    workerObject serviceObj(&app,endPoints);
    serviceObj.moveToThread(&workerThread);

    QObject::connect(&workerThread, SIGNAL(started()), &serviceObj, SLOT(startObject()));
    QObject::connect(&workerThread, SIGNAL(finished()), &serviceObj, SLOT(stopObject()));
    workerThread.start();
    QObject::connect(QThread::currentThread(), SIGNAL(quit()), &workerThread, SLOT(quit()));


    QQmlApplicationEngine engine;

    // Birinci QML dosyası ekleme
    const QUrl url("qrc:/Main.qml");


    //End point class definition should be done before engine load but initilized
    QQmlContext * Context1 = engine.rootContext();
    Context1->setContextProperty("endPoints", endPoints);

    engine.load(url);

    return app.exec();
}

