#ifndef SAVED_HPP
#define SAVED_HPP

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QPair>
#include <QThread>
#include <QCoreApplication>

#include "Cpp/model.hpp"
#include "Cpp/vkapi.hpp"

class Saved : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel *model READ getModel NOTIFY modelChanged)
    Q_PROPERTY(QString accessToken WRITE setAccessToken)

public:
    explicit Saved(QObject *parent = nullptr);
    /*virtual*/ ~Saved();

private:
    QString accessToken;
    void setAccessToken(QString);

    QVector<int> friends;
    void getFriends();

    QVector<int> users;

    Model *model;
    Model *getModel();

    void start();
    void getSaved(int);
    QPair<QString, QString> getAccountInfo(int);

    VKApi *api;

signals:
    void modelChanged();

};

#endif // SAVED_HPP
