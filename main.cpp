#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Cpp/login.hpp"
#include "Cpp/saved.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Login>("LoginBackend", 1, 0, "LoginBackend");
    qmlRegisterType<Saved>("SavedBackend", 1, 0, "SavedBackend");
    qmlRegisterType<Saved>("CaptchaBackend", 1, 0, "CaptchaBackend");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
