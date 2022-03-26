#ifndef IBANKSYSTEMMODEL_H
#define IBANKSYSTEMMODEL_H

#include <string>

#include "nouserindbexception.h"

class IBankSystemModel
{
public:
    // Установить банк, с которым будет работать система.
    virtual void setCurrentBank(std::string bankName) = 0;

    // войти в систему.
    // Если юзера с таким логином или паролем нет, выкинуть исключение NoUserInDBException
    virtual void enter(const std::string& login, const std::string& password) = 0;
};

#endif // IBANKSYSTEMMODEL_H
