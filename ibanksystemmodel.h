#ifndef IBANKSYSTEMMODEL_H
#define IBANKSYSTEMMODEL_H

#include <string>
#include <list>

#include "bank.h"
#include "client.h"
#include "account.h"
#include "deposit.h"
#include "credit.h"
#include "nouserindbexception.h"

class IBankSystemModel
{
public:
    virtual std::list<Bank *> loadBanksList() = 0;

    // Установить банк, с которым будет работать система.
    virtual void setCurrentBank(std::string bankName) = 0;
    virtual void setCurrentBank(Bank *bank) = 0;

    virtual Bank *getCurrentBank() = 0;

    // войти в систему.
    // Если юзера с таким логином или паролем нет, выкинуть исключение NoUserInDBException
    virtual void enter(std::string login, std::string password) = 0;

    // Подать запрос на регистрацию клиента, который должен быть одобрен менеджером
    virtual void sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                            std::string name, std::string phone, std::string passportData,
                                            bool fromRB) = 0;

    // Зарегистрировать в базе данных предприятие
    virtual void registerEnterprise(std::string type, std::string name,
                                    int64_t pan, int64_t bic, std::string address) = 0;

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
    virtual void openAccountForClient(Client *client, int *id = nullptr) = 0;

    // Открыть вклад
    virtual void openDepositForClient(Client *client, int term, double sum) = 0;

    // Получить все счета, хранящиеся в банке
    virtual std::list<Account *> getAllAccounts() = 0;

    // Получить все вклады, хранящиеся в банке
    virtual std::list<Deposit *> getAllDeposits() = 0;

    // Получить ВСЕ счета клиента в банке
    virtual std::list<Account *> getClientAccounts(Client *client) = 0;

    // Получить ВСЕ вклады клиента в банке
    virtual std::list<Deposit *> getClientDeposits(Client *client) = 0;

    // Получить ВСЕ кредиты клиента в банке
    virtual std::list<Credit *> getClientCredits(Client *client) = 0;

    // Получить счета клиента в банке с определённым статусом
    virtual std::list<Account *> getClientAccountsByStatus(Client *client, int requiredStatus) = 0;

    // Получить ВКЛАДЫ клиента в банке с определённым статусом
    virtual std::list<Deposit *> getClientDepositsByStatus(Client *client, int requiredStatus) = 0;

    // Проверить, может ли клиент взять такой кредит
    virtual bool clientCanTakeLoan(std::string clientLogin, double loanValueUsd) = 0;

    // Получить либо счёт, либо вклад по id
    virtual SomethingHoldingMoney *getSomethingHoldingMoneyById(int64_t id, std::string *table = nullptr) = 0;

    // Закрыть счёт или вклад. Если закрыть невозможно, выкинуть исключение CannotCloseSHMException
    virtual void close(int64_t id) = 0;

    // Заморозить счёт или вклад
    virtual void freeze(int64_t id) = 0;

    // Заблокировать счёт или вклад
    virtual void ban(int64_t id) = 0;

    // Получить счёт из базы по id
    virtual Account *getAccountById(int64_t id) = 0;

    // Получить вклад из базы по id
    virtual Deposit *getDepositById(int64_t id) = 0;

    // Обновить баланс (начислить проценты) и время обновления баланса (для счёта)
    virtual void clientAccountAccumulate(int64_t id) = 0;

    // Проверить, не истёк ли срок вклада
    virtual void clientDepositCheckTerm(int64_t id) = 0;

    // Обновить баланс (начислить проценты) и время обновления баланса (для вклада)
    virtual void clientDepositAccumulate(int64_t id) = 0;

    // Обновить информацию о счёте
    virtual void updateAccountData(Account *acc) = 0;

    // Обновить информацию о вкладе
    virtual void updateDepositData(Deposit *dep) = 0;

    // Положить деньги на счёт
    virtual void putMoneyOnAccount(int64_t id, double value) = 0;

    // Снять деньги со счёта
    virtual void withdrawMoneyFromAccount(int64_t id, double value) = 0;

    // Оформить перевод со счёта на счёт
    virtual void createTransfer(int64_t sender, int64_t recipient, double value) = 0;

    // Оформить кредит
    virtual void createCredit(int months, double value, Currency currency, double monthlyPercents,
                              time_t creationTime, std::string clientLogin) = 0;

    // Заплатить по кредиту
    virtual void payCredit(int64_t id, double value) = 0;

    // Запустить определённые тесты
    virtual void test() = 0;
};

#endif // IBANKSYSTEMMODEL_H
