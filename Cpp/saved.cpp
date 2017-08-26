#include "saved.hpp"

Saved::Saved(QObject *parent) : QObject(parent)
{
    model = new Model;
    api = new VKApi;

    settings.setDefaultFormat(QSettings::NativeFormat);
    users = settings.value("users").value<QVector<unsigned int>>();
    users = settings.value("blackList").value<QVector<unsigned int>>();

//    users.append(448499);
//    users.append(3471583);
}

Saved::~Saved()
{
    delete api;
    delete model;
}

void Saved::update()
{
    updateAccounts();
    updateSaved();
}

void Saved::updateAccounts()
{
    QList<unsigned int> tempList = QSet<unsigned int>(QSet<unsigned int>::fromList(getFriends().toList())
                        + QSet<unsigned int>::fromList(users.toList())
                        - QSet<unsigned int>::fromList(blackList.toList())).toList();
    for (QList<unsigned int>::iterator it = tempList.begin(); it != tempList.end(); ++it) {
        accountsList.append(Account(*it));
    }
    accountsCount = accountsList.count();
    emit accountsListChanged();
}

void Saved::updateSaved()
{
    for (QList<Account>::iterator it = accountsList.begin(); it <= accountsList.end(); ++it) {
        emit progressChanged();
        QCoreApplication::processEvents();
        try {
            getSaved(*it);
        } catch (VKError error) {
            qDebug() << error.message();
            switch (error.code()) {
            case 6:
                --it;
                break;
            case 15:
                accountsList.erase(it);
                break;
            case 200:
                accountsList.erase(it);
                break;
            default:
                qDebug() << "VKError: " << error.code();
                break;
            }
        } catch (RequestError error) {
            qDebug() << error.message();
        } catch (...) {
            qDebug() << "UNDEFINE ERROR";
        }
    }
}

Model *Saved::getModel()
{
    return model;
}

QVector<unsigned int> Saved::getFriends()
{
    QJsonObject jsonObject = api->get("friends.get?"
                                      "access_token="
                                    + accessToken).toObject();
    int count = jsonObject.value("count").toInt(0);
    QJsonArray jsonArray = jsonObject.value("items").toArray();
    QVector<unsigned int> friends;
    for (int i = 0; i < count; ++i) {
        friends.append(static_cast<unsigned int>(jsonArray.at(i).toInt()));
    }
    return friends;
}

QPair<QString, QString> Saved::getAccountInfo(int id)
{
    QJsonObject jsonObject = api->get("users.get?user_ids="
                                         + QString::number(id)
                                         + "&fields=photo_50"
                                           "&access_token="
                                         + accessToken).toArray().at(0).toObject();
    QString name = QString(jsonObject.value("first_name").toString() + " "
                           + jsonObject.value("last_name").toString());
    QString photo = QString(jsonObject.value("photo_50").toString());
    return QPair<QString, QString>(name, photo);
}

void Saved::getSaved(Account &account, int offset)
{
    QJsonValue jsonValue = api->get("photos.get?"
                                    "owner_id="
                                  + QString::number(account.getID())
                                  + "&album_id=saved"
                                    "&rev=1"
                                    "&offset="
                                  + QString::number(offset)
                                  + "&access_token="
                                  + accessToken);
    qDebug() << "Done";

    int count = jsonValue.toObject().value("count").toInt(0);

    QJsonArray jsonArray = jsonValue.toObject().value("items").toArray();

    QPair<QString, QString> pair = getAccountInfo(jsonArray.at(0).toObject().value("owner_id").toInt());
    QString name = pair.first;
    QString photo = pair.second;

    qDebug() << "Last image ID" << account.getLastImageID();

    for (auto i: jsonArray) {
        unsigned int date = static_cast<unsigned int>(i.toObject().value("date").toInt());
        unsigned int imageID = static_cast<unsigned int>(i.toObject().value("id").toInt());
//        qDebug() << "Image ID" << imageID;
        if (imageID == account.getLastImageID())
            return;

        QString image;
        if (i.toObject().value("photo_2560") != QJsonValue::Undefined)
            image = i.toObject().value("photo_2560").toString();
        else if (i.toObject().value("photo_1280") != QJsonValue::Undefined)
            image = i.toObject().value("photo_1280").toString();
        else if (i.toObject().value("photo_807") != QJsonValue::Undefined)
            image = i.toObject().value("photo_807").toString();
        else if (i.toObject().value("photo_604") != QJsonValue::Undefined)
            image = i.toObject().value("photo_604").toString();
        else if (i.toObject().value("photo_130") != QJsonValue::Undefined)
            image = i.toObject().value("photo_130").toString();
        else if (i.toObject().value("photo_75") != QJsonValue::Undefined)
            image = i.toObject().value("photo_75").toString();

        double ratio = i.toObject().value("height").toDouble() / i.toObject().value("width").toDouble();

        model->addPhoto(Photo(photo, name, date, image, ratio));
        QCoreApplication::processEvents();
    }
    emit modelChanged();

    if (offset == 0)
        account.setLastIMageID(static_cast<unsigned int>(jsonArray[0].toObject().value("id").toInt()));

    qDebug() << account.getLastImageID();

    if ((offset + 1000) < count && offset == 0) {
        getSaved(account, offset + 1000);
    }
}

int Saved::getAccountCounts() const
{
    return accountsCount;
}

void Saved::readAccessToken()
{
    if (!settings.value("access_token").isNull()) {
        accessToken = settings.value("access_token").toString();
    }
    else {
        qDebug() << "Access token error!";
    }   
}
