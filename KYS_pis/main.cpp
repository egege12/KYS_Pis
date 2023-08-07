#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QQmlContext>
#include "workerobject.h"
#include <QLocalServer>
#include <QLocalSocket>

int main(int argc, char *argv[])
{

    QLocalSocket socket;
    socket.connectToServer("my_unique_key");
    if (socket.waitForConnected(500)) {
        qDebug() << "Another instance is already running.";
        return 0;
    }
    QLocalServer server;
    if (!server.listen("my_unique_key")) {
        qDebug() << "Server could not start. Another instance is already running.";
        return 1;
    }
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
    QObject::connect(QThread::currentThread(), SIGNAL(aboutToQuit()), &serviceObj, SLOT(stopObject()));
    QObject::connect(&app, SIGNAL(aboutToQuit()), &workerThread, SLOT(quit()));
    QQmlApplicationEngine engine;
    // Birinci QML dosyası ekleme
    const QUrl url("qrc:/Main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    //End point class definition should be done before engine load but initilized
    QQmlContext * Context1 = engine.rootContext();
    Context1->setContextProperty("dataPoints", endPoints);

    engine.load(url);

    return app.exec();
}

