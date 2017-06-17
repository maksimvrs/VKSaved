#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QObject>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LOGIN_HPP