#include "login.hpp"

Login::Login(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(connectionComplete()),
            this, SLOT(saveAccessToken()));

    if (!settings.value("access_token").isNull()) {
        accessToken = settings.value("access_token").toString();
        qDebug() << "Access token: " << accessToken;
        haveAccessToken = true;
    }
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

bool Login::_haveAccessToken() const
{
    qDebug() << "Request haveAccessToken: " << haveAccessToken;
    return haveAccessToken;
}

QString Login::getCaptchaSource() const
{
    return captchaSource;
}

void Login::getAccessToken()
{
    _getAccessToken("");
}

QString Login::readAccessToken() const
{
    return accessToken;
}

void Login::_getAccessToken(QString append = "")
{
    QUrl request = "https://oauth.vk.com/token?grant_type=password&"
                   "client_id=" + clientID
                 + "&client_secret=" + clientSecret
                 + "&scpoe=" + scope
                 + "&username=" + login
                 + "&password=" + password
                 + "&v=" + apiVersion
                 + append;

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            manager, SLOT(deleteLater()));

    manager->get(QNetworkRequest(request));

    qDebug() << "Http GET request: " << request.toString();
}

void Login::replyFinished(QNetworkReply *reply)
{
    QString replyStr = reply->readAll();

    reply->abort();
    reply->deleteLater();

    manager->deleteLater();

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
    captchaSource = jsonObject.value("captcha_img").toString() + "&image.jpg";
    captchaID = jsonObject.value("captcha_sid").toString();
    emit captchaRequest();
}

void Login::captchaInput(QString key)
{
    qDebug() << "Captcha input: " << key;
    _getAccessToken("&captcha_sid=" + captchaID
                 + "&captcha_key=" + key);
}

void Login::saveAccessToken()
{
    settings.setValue("access_token", accessToken);
    qDebug() << "Access token was saved: "<< accessToken;
}

void Login::exit()
{
    haveAccessToken = false;
    settings.remove("access_token");
}
