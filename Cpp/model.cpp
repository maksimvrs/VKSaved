#include "model.hpp"

Photo::Photo(const QString &profilePhoto,
             const QString &profileName,
             const unsigned int &date,
             const QString &image,
             const double &ratio)
    : m_profilePhoto(profilePhoto),
      m_profileName(profileName),
      m_date(date),
      m_image(image),
      m_ratio(ratio)
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

unsigned int Photo::date() const
{
    return m_date;
}

QString Photo::dateString() const
{
    return  QDateTime::fromTime_t(m_date).toString("HH:mm:ss - d MMMM yyyy");
}

QString Photo::image() const
{
    return m_image;
}

double Photo::ratio() const
{
    return m_ratio;
}

Model::Model(QObject *parent)
    : QAbstractListModel(parent)
{
}

void Model::addPhoto(const Photo &photo)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for (QList<Photo>::iterator it = m_photos.begin(); it != m_photos.end(); ++it) {
        if (photo.date() > (*it).date()) {
            m_photos.insert(it, photo);
            goto breakPoint;
        }
    }
    m_photos.append(photo);
    breakPoint:
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
        return photo.dateString();
    else if (role == imageRole)
        return photo.image();
    else if (role == ratioRole)
        return photo.ratio();
    return QVariant();
}

QHash<int, QByteArray> Model::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[profilePhotoRole] = "profilePhoto";
    roles[profileNameRole] = "profileName";
    roles[dateRole] = "date";
    roles[imageRole] = "image";
    roles[ratioRole] = "ratio";
    return roles;
}
