#ifndef SAVED_HPP
#define SAVED_HPP

#include <QObject>

class Saved : public QObject
{
    Q_OBJECT
public:
    explicit Saved(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SAVED_HPP