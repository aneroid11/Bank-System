#ifndef BANKSYSTEMMODEL_H
#define BANKSYSTEMMODEL_H

#include "ibanksystemmodel.h"

class Database;

class BankSystemModel : public IBankSystemModel
{
public:
    BankSystemModel();
    ~BankSystemModel();

    std::list<Bank *> loadBanksList() override;

    void setCurrentBank(std::string bankName) override;
    void setCurrentBank(Bank *bank) override;

    Bank *getCurrentBank() override { return currentBank; }

    void enter(std::string login, std::string password) override;

    void sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                    std::string name, std::string phone, std::string passportData,
                                    bool fromRB) override;

    void registerEnterprise(std::string type, std::string name,
                            int64_t pan, int64_t bic, std::string address) override;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    void addSampleOperator() override;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    void addSampleManager() override;

    // TODO: заменить на нормальное появление в базе данных менеджеров, администраторов и операторов
    void addSampleAdministrator() override;

    User *getUserData(std::string login, std::string &type) override;

    std::list<Client *> getUnapprovedClients() override;

    void approveClient(std::string login) override;

    void openAccountForClient(Client *client, int *id = nullptr) override;

    void openDepositForClient(Client *client, int term, double sum) override;

    std::list<Account *> getAllAccounts() override;

    std::list<Deposit *> getAllDeposits() override;

    std::list<Account *> getClientAccounts(Client *client) override;

    std::list<Deposit *> getClientDeposits(Client *client) override;

    std::list<SomethingHoldingMoney *> getClientSmthHoldingMoneyByStatus(Client *client,
                                                                         int requiredStatus,
                                                                         std::string table);

    std::list<Account *> getClientAccountsByStatus(Client *client, int requiredStatus) override;

    std::list<Deposit *> getClientDepositsByStatus(Client *client, int requiredStatus) override;

    bool clientCanTakeLoan(std::string clientLogin, double loanValueUsd) override;

    SomethingHoldingMoney *getSomethingHoldingMoneyById(int64_t id, std::string *table = nullptr) override;

    Account *getAccountById(int64_t id) override;

    Deposit *getDepositById(int64_t id) override;

    void setSmthHoldingMoneyStatus(int64_t id, int status);

    void close(int64_t id) override;

    void freeze(int64_t id) override;

    void ban(int64_t id) override;

    void clientAccountAccumulate(int64_t id) override;

    void clientDepositCheckTerm(int64_t id) override;

    void clientDepositAccumulate(int64_t id) override;

    void updateAccountData(Account *acc) override;

    void updateDepositData(Deposit *dep) override;

    void putMoneyOnAccount(int64_t id, double value) override;

    void withdrawMoneyFromAccount(int64_t id, double value) override;

    void createTransfer(int64_t sender, int64_t recipient, double value);

    void createCredit(int months, double value, Currency currency,
                      double monthlyPercents, time_t creationTime, std::string clientLogin) override;

    void test() override;

private:
    Database *database = nullptr;

    std::list<Bank *> banksList;
    Bank *currentBank;
    //std::string currentBank = "";
};

#endif // BANKSYSTEMMODEL_H
