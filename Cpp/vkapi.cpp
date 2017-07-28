#include "vkapi.hpp"

VKApi::VKApi(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}


VKApi::~VKApi()
{
    delete manager;
}

void VKApi::get(QString addRequest)
{
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
    QNetworkReply *reply = managerTemp->get(QNetworkRequest(request));

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
    if (reply->error() != QNetworkReply::NoError) {

        qWarning() << "Request error: " << reply->errorString();
        // Request error

        return QJsonObject();
    }

    QString replyStr = reply->readAll();

    reply->deleteLater();

    qDebug() << "Http get reply: " << replyStr;

    QJsonObject jsonObject = QJsonDocument::fromJson(replyStr.toUtf8()).object();
    if (jsonObject.value("error") != QJsonValue::Undefined) {

        qWarning() << "Http get ERROR: : " << jsonObject.value("error");

        QString errorCode = jsonObject.value("error_code").toString(),
                errorMessage = jsonObject.value("error_msg").toString();

        qWarning() << "VK error";
        // VK error

        return QJsonObject();
    }
    else if (jsonObject.value("response") != QJsonValue::Undefined) {
        return jsonObject.value("response");
    }
    else {

        qWarning() << "VK undefined error";
        // VK undefined error

        return QJsonObject();
    }
}
