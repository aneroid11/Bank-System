#ifndef CANNOTADDUSERDBEXCEPTION_H
#define CANNOTADDUSERDBEXCEPTION_H

#include "dbexception.h"

class CannotAddUserDBException : public DBException
{
public:
    CannotAddUserDBException(std::string errMsg) : DBException(errMsg) {}
};

#endif // CANNOTADDUSERDBEXCEPTION_H
