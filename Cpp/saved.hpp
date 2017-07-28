#ifndef SAVED_HPP
#define SAVED_HPP

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QPair>

#include "Cpp/model.hpp"
#include "Cpp/vkapi.hpp"

class Saved : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel *model READ getModel NOTIFY modelChanged)

public:
    explicit Saved(QObject *parent = nullptr);
    /*virtual*/ ~Saved();

private:
    QString accessToken;

    QVector<int> friends;

    Model *model;
    Model *getModel();

    void getFriends();

    void getImageAndDate(int);
    QPair<QString, QString> getNameAndPhoto(int);

    VKApi *api;
signals:
    void modelChanged();

private slots:
    void replyFinished(QJsonValue);

};

#endif // SAVED_HPP
