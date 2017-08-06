#ifndef VKAPI_HPP
#define VKAPI_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QThread>

#include <Cpp/exceptions.hpp>

class VKApi : public QObject
{
    Q_OBJECT
public:
    explicit VKApi(QObject *parent = nullptr);
    ~VKApi();
    QJsonValue get(QString);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QEventLoop *loop;
    QTime *time;
    QJsonValue parseResponse(QNetworkReply*);

    // Configuration
    static constexpr int mInterval = 334;

    static constexpr double version = 5.67;

};

#endif // VKAPI_HPP
