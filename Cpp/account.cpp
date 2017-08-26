#include "account.hpp"

Account::Account(unsigned int id, unsigned int lastImageID, unsigned int lastImageDate)
    : id(id)
    , lastImageID(lastImageID)
    , lastImageDate(lastImageDate)
{

}

unsigned int Account::getID() const
{
    return id;
}

void Account::setLastIMageID(unsigned int _lastImageID)
{
    lastImageID = _lastImageID;
}

unsigned int Account::getLastImageID() const
{
    return lastImageID;
}

void Account::setLastImageDate(unsigned int _lastImageDate)
{
    lastImageDate = _lastImageDate;
}

unsigned int Account::getLastImageDate() const
{
    return lastImageDate;
}
