#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Cpp/login.hpp"
#include "Cpp/saved.hpp"
#include <Cpp/model.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Login>("LoginBackend", 1, 0, "LoginBackend");
    qmlRegisterType<Saved>("SavedBackend", 1, 0, "SavedBackend");
    qmlRegisterType<Saved>("CaptchaBackend", 1, 0, "CaptchaBackend");

    QQmlApplicationEngine engine;

    Model model;

    QQmlContext *context = new QQmlContext(engine.rootContext());
    context->setContextProperty("photosModel", &model);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
