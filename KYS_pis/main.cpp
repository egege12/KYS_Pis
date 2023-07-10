#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include "workerobject.h"
int main(int argc, char *argv[])
{

    QThread workerThread;
    QThread::currentThread()->setObjectName("Main Thread");
    workerThread.setObjectName("Backend Thread");
    workerObject httpService;
    httpService.moveToThread(&workerThread);



    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Birinci QML dosyası ekleme
    const QUrl url("qrc:/Main.qml");


    engine.load(url);

    return app.exec();
}

