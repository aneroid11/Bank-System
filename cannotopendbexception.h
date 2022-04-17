#ifndef CANNOTOPENDBEXCEPTION_H
#define CANNOTOPENDBEXCEPTION_H

#include "dbexception.h"

class CannotOpenDBException : public DBException
{
public:
    CannotOpenDBException(std::string errMsg) : DBException(errMsg) {}
};

#endif // CANNOTOPENDBEXCEPTION_H
