#ifndef IBANKSYSTEMMODEL_H
#define IBANKSYSTEMMODEL_H

#include <string>

class IBankSystemModel
{
public:
    // войти в систему. Если юзера с таким логином или паролем нет, выкинуть исключение.
    virtual void enter(const std::string& login, const std::string& password) = 0;
};

#endif // IBANKSYSTEMMODEL_H
