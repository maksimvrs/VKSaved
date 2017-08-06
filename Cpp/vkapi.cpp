#include "vkapi.hpp"

VKApi::VKApi(QObject *parent) : QObject(parent)
{
}


VKApi::~VKApi()
{
}

void VKApi::get(QString addRequest)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    QUrl request = QString("https://api.vk.com/method/"
                      + addRequest
                      + "&v=" + QString::number(version));
    manager->get(QNetworkRequest(request));

    qDebug() << "Http get request: " << request.toString();
}

QJsonValue VKApi::getNow(QString addRequest)
{
    QNetworkAccessManager *managerTemp = new QNetworkAccessManager(this);
    QUrl request = QString("https://api.vk.com/method/"
                      + addRequest
                      + "&v=" + QString::number(version));

    if (time.elapsed() < mInterval) {
        QThread::msleep(static_cast<unsigned long>(mInterval - time.elapsed()));
    }

    QNetworkReply *reply = managerTemp->get(QNetworkRequest(request));

    time = QTime::currentTime();

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    managerTemp->deleteLater();

    return processResponse(reply);
}

void VKApi::replyFinished(QNetworkReply *reply)
{
    emit finished(processResponse(reply));
}

QJsonValue VKApi::processResponse(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
        throw RequestError(reply->errorString());

    QString replyStr = reply->readAll();

    reply->manager()->deleteLater();
    reply->deleteLater();

    qDebug() << "Http get reply: " << replyStr;

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
