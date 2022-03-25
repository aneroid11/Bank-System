#ifndef CANNOTCREATETABLEDBEXCEPTION_H
#define CANNOTCREATETABLEDBEXCEPTION_H

#include "dbexception.h"

class CannotCreateTableDBException : public DBException
{
public:
    CannotCreateTableDBException(std::string errMsg) : DBException(errMsg) {}
};

#endif // CANNOTCREATETABLEDBEXCEPTION_H
