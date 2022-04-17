#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <list>

#include <QSqlDatabase>

#include "user.h"

//struct sqlite3;
class Client;
class Manager;
class Operator;
class Administrator;
class Account;
class Deposit;
class Transfer;
class SomethingHoldingMoney;
class Credit;
class Enterprise;

struct UserRawData
{
    bool hasData() const { return columnNames.size(); }

    std::vector<std::string> columnNames;
    std::vector<std::string> rowFields;
};

class Database
{
public:
    Database(std::string filename);
    ~Database();

    void addClient(const Client &client);
    void addManager(const Manager &manager);
    void addOperator(const Operator &op);
    void addAdministrator(const Administrator &admin);

    void addTransfer(const Transfer &transfer);
    void addCredit(const Credit &credit);

    void addAccount(const Account &account);
    void addDeposit(const Deposit &deposit);

    void addEnterprise(const Enterprise &enterprise);
    bool hasEnterpriseWithName(std::string name);
    bool hasEnterpriseWithPan(int64_t pan);

    void deleteUser(int64_t id);

    bool hasUserWith(std::string parameterName, std::string parameterValue);
    bool hasUser(int64_t id);
    bool hasUser(std::string login);
    bool hasUserWithPassportData(std::string passportData);

    bool hasRecord(int64_t id);
    bool hasRecordWith(std::string tableName, std::string parameterName, std::string parameterValue);

    void approveClient(std::string login);

    int64_t generateUniqueUserId();
    int64_t generateUniqueId();

    std::list<User *> getUsersFromTableByParameter(std::string tableName, std::string parameterName,
                                                   std::string parameterValue);
    std::list<void *> getAllRecordsFromTable(std::string tableName);
    std::list<void *> getRecordsFromTableByParameter(std::string tableName, std::string parameterName,
                                                     std::string parameterValue);

    std::list<Client *> getUnapprovedClients();

    std::list<Account *> getAllAccounts();
    std::list<Deposit *> getAllDeposits();

    std::list<Account *> getClientAccounts(std::string clientLogin);

    // Получить по логину пользователя и его роль в системе (записывается в переменную type)
    User *getUserData(std::string login, std::string &type);

    void updateAccount(Account *data);
    void updateDeposit(Deposit *data);
    void updateCredit(Credit *data);

private:
    void createClientsTable();
    void createOperatorsTable();
    void createManagersTable();
    void createAdministratorsTable();
    void createAccountsTable();
    void createDepositsTable();
    void createTransfersTable();
    void createEnterprisesTable();
    void createCreditsTable();

    User *createUserFromData(const QSqlQuery &query, const QSqlRecord &rec, std::string tableName);
    void *createRecordFromData(const QSqlQuery &query, const QSqlRecord &rec, std::string tableName);

    QSqlDatabase database;
};

#endif // DATABASE_H
