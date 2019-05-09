#include <QGuiApplication>

#include "tortoise.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("Pric0");
    QCoreApplication::setOrganizationDomain("PrApps");
    QCoreApplication::setApplicationName("Черепаха");
    QCoreApplication::setApplicationVersion("3.3");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Tortoise tortoise(&engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
