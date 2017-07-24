#ifndef MODEL_HPP
#define MODEL_HPP

#include <QAbstractListModel>
#include <QStringList>

#include <QDebug>

class Photo
{
public:
    Photo(const QString &profilePhoto,
          const QString &profileName,
          const QString &date,
          const QString image);

    QString profilePhoto() const;
    QString profileName() const;
    QString date() const;
    QString image() const;

private:
    QString m_profilePhoto;
    QString m_profileName;
    QString m_date;
    QString m_image;
};

class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AnimalRoles {
        profilePhotoRole = Qt::UserRole + 1,
        profileNameRole,
        dateRole,
        imageRole
    };

    Model(QObject *parent = 0);

    void addPhoto(const Photo &photo);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Photo> m_photos;

};

#endif // MODEL_HPP
