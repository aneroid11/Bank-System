#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#include "user.h"

struct sqlite3;
class Client;
class Manager;

class Database
{
public:
    Database(std::string filename);
    ~Database();

    void addClient(const Client &client);
    void addManager(const Manager &manager);

    void deleteUser(int64_t id);
    bool hasUser(int64_t id);
    bool hasUser(std::string login);

    //void approveClient(std::string login);

    int64_t generateUniqueUserId();

    // Получить по логину пользователя и его роль в системе (записывается в переменную type)
    User *getUserData(std::string login, std::string &type);

private:
    void createClientsTable();
    void createOperatorsTable();
    void createManagersTable();
    void createAdministratorsTable();

    sqlite3 *database;
};

#endif // DATABASE_H
