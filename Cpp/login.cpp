#include "login.hpp"

Login::Login(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

Login::~Login()
{
    delete manager;
}

void Login::setLogin(QString& _login)
{
    login = _login;
}

void Login::setPassword(QString& _password)
{
    password = _password;
}

QString Login::getCaptchaSource() const
{
    return captchaSource;
}

void Login::getAccessToken()
{
    _getAccessToken("");
}

void Login::_getAccessToken(QString append = "")
{
    QUrl request = "https://oauth.vk.com/token?grant_type=password&"
                   "client_id=" + clientID
                 + "&client_secret=" + clientSecret
                 + "&username=" + login
                 + "&password=" + password
                 + "&v=" + apiVersion
                 + append;

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(request));

    qDebug() << "Http GET request: " << request.toString();
}

void Login::replyFinished(QNetworkReply *reply)
{
    QString replyStr = reply->readAll();
    qDebug() << "Http GET reply: " << replyStr;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(replyStr.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    if (jsonObject.value("error") != QJsonValue::Undefined) {
        qDebug() << "Http GET error: " << jsonObject.value("error").toString();
        if (jsonObject.value("error").toString() == "need_captcha")
            captcha(jsonObject);
    }
    else if (jsonObject.value("access_token") != QJsonValue::Undefined){
        accessToken = jsonObject.value("access_token").toString();
        emit connectionComplete();
        qDebug() << "Connection complete!";
        qDebug() << "Access token: " << accessToken;
    }
    else {
        // ERROR
    }
}

void Login::captcha(QJsonObject& jsonObject)
{
    qDebug() << "Captcha: " << jsonObject.value("captcha_img").toString();
    captchaSource = jsonObject.value("captcha_img").toString();
    captchaID = jsonObject.value("captcha_sid").toString();
    emit captchaRequest();
}

void Login::captchaInput(QString &key)
{
    _getAccessToken("&captcha_sid=" + captchaID
                 + "&captcha_key=" + key);
}
