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
    void addAccount(const Account &account);

    void deleteUser(int64_t id);
    bool hasUser(int64_t id);
    bool hasUser(std::string login);

    bool hasRecord(int64_t id);

    void approveClient(std::string login);

    int64_t generateUniqueUserId();
    int64_t generateUniqueId();

    std::list<User *> getUsersFromTableByParameter(std::string tableName, std::string parameterName,
                                                   std::string parameterValue);
    std::list<void *> getRecordsFromTableByParameter(std::string tableName, std::string parameterName,
                                                     std::string parameterValue);

    std::list<Client *> getUnapprovedClients();
    std::list<Account *> getClientAccounts(std::string clientLogin);

    // Получить по логину пользователя и его роль в системе (записывается в переменную type)
    User *getUserData(std::string login, std::string &type);

private:
    void createClientsTable();
    void createOperatorsTable();
    void createManagersTable();
    void createAdministratorsTable();
    void createAccountsTable();

    User *createUserFromData(const QSqlQuery &query, const QSqlRecord &rec, std::string tableName);
    void *createRecordFromData(const QSqlQuery &query, const QSqlRecord &rec, std::string tableName);

    QSqlDatabase database;
    //sqlite3 *database;
};

#endif // DATABASE_H
