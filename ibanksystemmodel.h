#ifndef IBANKSYSTEMMODEL_H
#define IBANKSYSTEMMODEL_H

#include <string>
#include <list>

#include "client.h"
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

    // Получить пользователя и его тип по логину
    virtual User *getUserData(std::string login, std::string &type) = 0;

    // Получить список клиентов, регистрация которых ещё не была подтверждена менеджером
    virtual std::list<Client *> getUnapprovedClients() = 0;

    // Запустить определённые тесты
    virtual void test() = 0;
};

#endif // IBANKSYSTEMMODEL_H
