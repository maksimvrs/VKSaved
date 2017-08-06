#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <QString>
#include <exception>

struct SavedError{
public:
    explicit SavedError(const QString&);
    virtual ~SavedError();
    virtual QString message() const noexcept;

private:
    QString errorMessage;

};

struct VKError: SavedError {
public:
    explicit VKError(const int&, const QString&);
    virtual int code() const noexcept;

private:
    const int errorCode;
};

struct RequestError: SavedError {
public:
    explicit RequestError(const QString&);
};

#endif // EXCEPTION_HPP
