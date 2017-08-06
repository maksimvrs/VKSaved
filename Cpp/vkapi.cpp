#include "vkapi.hpp"

VKApi::VKApi(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    loop = new QEventLoop(this);
    time = new QTime;
}


VKApi::~VKApi()
{
    delete time;
    delete loop;
    delete manager;
}

QJsonValue VKApi::get(QString addRequest)
{
    QUrl request = QString("https://api.vk.com/method/"
                      + addRequest
                      + "&v=" + QString::number(version));

    if (time->elapsed() < mInterval) {
        QThread::msleep(static_cast<unsigned long>(mInterval - time->elapsed()));
    }

    reply = manager->get(QNetworkRequest(request));
    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    *time = QTime::currentTime();
    loop->exec();
    disconnect(reply, SIGNAL(finished()), loop, SLOT(quit()));

    return parseResponse(reply);
}

QJsonValue VKApi::parseResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
        throw RequestError(reply->errorString());

    QString replyStr = reply->readAll();

    reply->deleteLater();

    QJsonObject jsonObject = QJsonDocument::fromJson(replyStr.toUtf8()).object();
    if (jsonObject.value("error") != QJsonValue::Undefined) {
        jsonObject = jsonObject.value("error").toObject();
        throw VKError(jsonObject.value("error_code").toInt(0),
                      jsonObject.value("error_msg").toString("VK undefined error."));
    }
    else if (jsonObject.value("response") != QJsonValue::Undefined)
        return jsonObject.value("response");
    else
        throw VKError(0, "VK unknown error.");
}
