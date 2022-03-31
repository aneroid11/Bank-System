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

    void deleteUser(int64_t id);
    bool hasUser(int64_t id);
    bool hasUser(std::string login);

    void approveClient(std::string login);

    int64_t generateUniqueUserId();

    std::list<User *> getUsersFromTableByParameter(std::string tableName, std::string parameterName,
                                                   std::string parameterValue);
    std::list<Client *> getUnapprovedClients();

    // Получить по логину пользователя и его роль в системе (записывается в переменную type)
    User *getUserData(std::string login, std::string &type);

private:
    void createClientsTable();
    void createOperatorsTable();
    void createManagersTable();
    void createAdministratorsTable();

    QSqlDatabase database;
    //sqlite3 *database;
};

#endif // DATABASE_H
