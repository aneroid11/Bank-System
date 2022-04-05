#ifndef BANKSYSTEMMODEL_H
#define BANKSYSTEMMODEL_H

#include "ibanksystemmodel.h"

class Database;

class BankSystemModel : public IBankSystemModel
{
public:
    BankSystemModel();
    ~BankSystemModel();

    void setCurrentBank(std::string bankName) override;

    void enter(std::string login, std::string password) override;

    void sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                    std::string name, std::string phone) override;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    void addSampleOperator() override;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    void addSampleManager() override;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    void addSampleAdministrator() override;

    User *getUserData(std::string login, std::string &type) override;

    std::list<Client *> getUnapprovedClients() override;

    void approveClient(std::string login) override;

    void openAccountForClient(Client *client) override;

    std::list<Account *> getClientAccounts(Client *client) override;

    void clientAccountAccumulate(int64_t idn) override;

    void updateAccountData(Account *acc) override;

    void putMoneyOnAccount(int64_t id, double value) override;

    void test() override;

private:
    Database *database = nullptr;

    std::string currentBank = "";
};

#endif // BANKSYSTEMMODEL_H
