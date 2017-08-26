#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP


class Account {
public:
    Account(unsigned int = 0, unsigned int = 0, unsigned int = 0);

    unsigned int getID() const;

    void setLastIMageID(unsigned int);
    unsigned int getLastImageID() const;

    void setLastImageDate(unsigned int);
    unsigned int getLastImageDate() const;

private:
    unsigned int id;
    unsigned int lastImageID;
    unsigned int lastImageDate;
};

#endif // ACCOUNT_HPP
