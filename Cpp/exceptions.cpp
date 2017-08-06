#include "exceptions.hpp"

SavedError::SavedError(const QString &message)
    : errorMessage(message)
{
}

SavedError::~SavedError()
{
}

QString SavedError::message() const noexcept
{
    return errorMessage;
}

VKError::VKError(const int &code, const QString &error)
    : SavedError(error)
    , errorCode(code)
{
}

int VKError::code() const noexcept
{
    return errorCode;
}

RequestError::RequestError(const QString &message)
    : SavedError(message)
{
}
