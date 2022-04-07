#ifndef IBANKSYSTEMMODEL_H
#define IBANKSYSTEMMODEL_H

#include <string>
#include <list>

#include "client.h"
#include "account.h"
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

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    virtual void addSampleOperator() = 0;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    virtual void addSampleAdministrator() = 0;

    // Получить пользователя и его тип по логину
    virtual User *getUserData(std::string login, std::string &type) = 0;

    // Получить список клиентов, регистрация которых ещё не была подтверждена менеджером
    virtual std::list<Client *> getUnapprovedClients() = 0;

    // Подтвердить регистрацию клиента
    virtual void approveClient(std::string login) = 0;

    // Открыть счёт
    virtual void openAccountForClient(Client *client) = 0;

    // Открыть вклад
    virtual void openDepositForClient(Client *client) = 0;

    // Получить ВСЕ счета клиента в банке
    virtual std::list<Account *> getClientAccounts(Client *client) = 0;

    // Получить счета клиента в банке с определённым статусом
    virtual std::list<Account *> getClientAccountsByStatus(Client *client, int requiredStatus) = 0;

    // Получить счёт из базы по id
    virtual Account *getAccountById(int64_t id) = 0;

    // Обновить баланс (начислить проценты) и время обновления баланса
    virtual void clientAccountAccumulate(int64_t id) = 0;

    // Обновить информацию о счёте
    virtual void updateAccountData(Account *acc) = 0;

    // Положить деньги на счёт
    virtual void putMoneyOnAccount(int64_t id, double value) = 0;

    // Снять деньги со счёта
    virtual void withdrawMoneyFromAccount(int64_t id, double value) = 0;

    // Оформить перевод со счёта на счёт
    virtual void createTransfer(int64_t sender, int64_t recipient, double value) = 0;

    // Запустить определённые тесты
    virtual void test() = 0;
};

#endif // IBANKSYSTEMMODEL_H
