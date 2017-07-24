#include "model.hpp"

Photo::Photo(const QString &profilePhoto,
             const QString &profileName,
             const QString &date,
             const QString image)
    : m_profilePhoto(profilePhoto),
      m_profileName(profileName),
      m_date(date),
      m_image(image)
{
}

QString Photo::profilePhoto() const
{
    return m_profilePhoto;
}

QString Photo::profileName() const
{
    return m_profileName;
}

QString Photo::date() const
{
    return m_date;
}

QString Photo::image() const
{
    return m_image;
}

Model::Model(QObject *parent)
    : QAbstractListModel(parent)
{
}

void Model::addPhoto(const Photo &photo)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_photos << photo;
    endInsertRows();
}

int Model::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_photos.count();
}

QVariant Model::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_photos.count())
        return QVariant();

    const Photo &photo = m_photos[index.row()];
    if (role == profilePhotoRole)
        return photo.profilePhoto();
    else if (role == profileNameRole)
        return photo.profileName();
    else if (role == dateRole)
        return photo.date();
    else if (role == imageRole)
        return photo.image();
    return QVariant();
}

QHash<int, QByteArray> Model::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[profilePhotoRole] = "profilePhoto";
    roles[profileNameRole] = "profileName";
    roles[dateRole] = "date";
    roles[imageRole] = "image";
    return roles;
}
