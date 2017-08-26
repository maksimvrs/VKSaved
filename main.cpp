#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Cpp/login.hpp"
#include "Cpp/saved.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Maksim Vorontsov");
    QCoreApplication::setApplicationName("Vk saved");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Login>("LoginBackend", 1, 0, "LoginBackend");
    qmlRegisterType<Saved>("SavedBackend", 1, 0, "SavedBackend");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
