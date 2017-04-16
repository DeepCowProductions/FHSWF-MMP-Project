#include <QApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include "glcore/myglitem.h"
#include "game/gamesceen.h"
#include <QDir>

int main(int argc, char *argv[])
{
    qDebug() << QDir::current();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //qmlRegisterType<MyGLItem>("MultiMediaProgrammierung", 1, 0, "MyGLItem");
    qmlRegisterType<GameSceen>("Spaceinvaders", 1, 0, "GameSceen");
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
