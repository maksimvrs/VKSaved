  #include "saved.hpp"

Saved::Saved(QObject *parent) : QObject(parent)
{
    model = new Model;
    api = new VKApi;

    connect(api, SIGNAL(finished(QJsonValue)),
            this, SLOT(replyFinished(QJsonValue)));

}

Saved::~Saved()
{
    delete model;
    delete api;
}

void Saved::setAccessToken(QString token)
{
    accessToken = token;
    start();
}

void Saved::start()
{
    getFriends();
    for (QVector<int>::iterator it = friends.begin(); it != friends.end(); ++it) {
        try {
            getImageAndDate(*it);
        } catch (VKError error) {
            qDebug() << error.code() << error.message();
            switch (error.code()) {
            case 6:
                --it;
            }
        } catch (RequestError error) {
            qDebug() << error.message();
        }
    }


//    getImageAndDate(3471583);
//    getImageAndDate(448499);
}

Model *Saved::getModel()
{
    return model;
}

void Saved::getFriends()
{
    QJsonObject jsonObject = api->getNow("friends.get?"
                                         "access_token="
                                         + accessToken).toObject();
    int count = jsonObject.value("count").toInt(0);
    QJsonArray jsonArray = jsonObject.value("items").toArray();
    for (int i = 0; i < count; ++i) {
        friends.append(jsonArray.at(i).toInt());
    }
}

QPair<QString, QString> Saved::getNameAndPhoto(int id)
{
    QJsonObject jsonObject = api->getNow("users.get?user_ids="
                                         + QString::number(id)
                                         + "&fields=photo_50"
                                           "&access_token="
                                         + accessToken).toArray().at(0).toObject();
    QString name = QString(jsonObject.value("first_name").toString() + " "
                           + jsonObject.value("last_name").toString());
    QString photo = QString(jsonObject.value("photo_50").toString());
    return QPair<QString, QString>(name, photo);
}

void Saved::getImageAndDate(int id)
{
    api->getNow("photos.get?"
             "owner_id="
           + QString::number(id)
           + "&album_id=saved"
             "&access_token="
           + accessToken);
}

void Saved::replyFinished(QJsonValue jsonValue)
{
    int count = jsonValue.toObject().value("count").toInt(0);
    if (count > 1000) {
        // Reply request
    }

    QJsonArray jsonArray = jsonValue.toObject().value("items").toArray();

    QPair<QString, QString> pair = getNameAndPhoto(jsonArray.at(0).toObject().value("owner_id").toInt());
    QString name = pair.first;
    QString photo = pair.second;

    for (auto i: jsonArray) {
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

        model->addPhoto(Photo(photo, name,
                              static_cast<unsigned int>(i.toObject().value("date").toInt()),
                              image, ratio));
    }
    emit modelChanged();
}
