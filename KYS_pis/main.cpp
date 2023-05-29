#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Birinci QML dosyası ekleme
    const QUrl url("qrc:/Main.qml");


    engine.load(url);

    return app.exec();
}

