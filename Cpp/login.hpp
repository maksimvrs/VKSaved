#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QTextCodec>

class Login : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString login WRITE setLogin)
    Q_PROPERTY(QString password WRITE setPassword)
    Q_PROPERTY(QString captchaSource READ getCaptchaSource)
    Q_PROPERTY(bool haveAccessToken READ _haveAccessToken)

public:
    explicit Login(QObject *parent = nullptr);
    /*virtual*/ ~Login();

    void setLogin(QString&);

    void setPassword(QString&);

    Q_INVOKABLE void getAccessToken();

    Q_INVOKABLE void captchaInput(QString);

    Q_INVOKABLE void exit();

    QString getCaptchaSource() const;

private:
    // User
    QString login;
    QString password;
    QString accessToken;
    QSettings settings;
    bool haveAccessToken = false;
    bool _haveAccessToken() const;

    // Application
    const QString clientID = "3697615";
    const QString clientSecret = "AlVXZFMUqyrnABp8ncuU";
    const QString scope = "photos";

    // API
    const QString apiVersion = "5.65";

    // Captcha
    QString captchaID;
    QString captchaSource;
    void captcha(QJsonObject&);

    // Request
    QNetworkAccessManager *manager;
    bool httpRequestAborted;

    void _getAccessToken(QString);
    void saveAccessToken();

signals:
    void captchaRequest();
    void connectionComplete();

private slots:
    void replyFinished(QNetworkReply*);

};

#endif // LOGIN_HPP
