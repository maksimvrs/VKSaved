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
#include "Cpp/account.hpp"

class Saved : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel *model READ getModel NOTIFY modelChanged)
    Q_PROPERTY(int accountsCount READ getAccountCounts NOTIFY accountsListChanged)

public:
    explicit Saved(QObject *parent = nullptr);
    /*virtual*/ ~Saved();

    Q_INVOKABLE void update();
    Q_INVOKABLE void readAccessToken();

    Q_INVOKABLE void updateAccounts();
    Q_INVOKABLE void updateSaved();

private:
    QString accessToken;

    QVector<unsigned int> getFriends();
    QVector<unsigned int> users;
    QVector<unsigned int> blackList;

    QList<Account> accountsList;

    int accountsCount;
    int getAccountCounts() const;

    QSettings settings;    

    Model *model;
    Model *getModel();

    void getSaved(Account&, int = 0);
    QPair<QString, QString> getAccountInfo(int);

    VKApi *api;

signals:
    void modelChanged();
    void progressChanged();
    void accountsListChanged();
};

#endif // SAVED_HPP
