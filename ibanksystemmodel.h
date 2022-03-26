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
    virtual void enter(std::string login, std::string password) = 0;

    // Подать запрос на регистрацию клиента, который должен быть одобрен менеджером
    virtual void sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                            std::string name, std::string phone) = 0;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    virtual void addSampleManager() = 0;
};

#endif // IBANKSYSTEMMODEL_H
