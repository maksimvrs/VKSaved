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

    void get(QString);
    QJsonValue getNow(QString);

private:
    QNetworkAccessManager *manager;

    QJsonValue processResponse(QNetworkReply*);

    QTime time;
    static constexpr int mInterval = 334;

    static constexpr double version = 5.67;

signals:
    void finished(QJsonValue);
    void error(int, QString);

private slots:
    void replyFinished(QNetworkReply*);

};

#endif // VKAPI_HPP
