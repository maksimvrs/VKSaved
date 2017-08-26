#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <QString>

// Base error
struct SavedError{
public:
    explicit SavedError(const QString&);
    virtual ~SavedError();
    virtual QString message() const noexcept;

private:
    QString errorMessage;

};

// Error vk api
struct VKError: SavedError {
public:
    explicit VKError(const int&, const QString&);
    virtual int code() const noexcept;

private:
    const int errorCode;
};


// Qt or network error
struct RequestError: SavedError {
public:
    explicit RequestError(const QString&);
};

#endif // EXCEPTION_HPP
