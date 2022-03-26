#include <iostream>

#include <sqlite3.h>

#include "database.h"
#include "hashcomputer.h"

#include "client.h"
#include "manager.h"

#include "cannotopendbexception.h"
#include "useralreadyexistsexception.h"

Database::Database(std::string filename)
{
    if (sqlite3_open(filename.c_str(), &database))
    {
        throw CannotOpenDBException(sqlite3_errmsg(database));
    }

    createClientsTable();
    createOperatorsTable();
    createManagersTable();
    createAdministratorsTable();
}

Database::~Database()
{
    sqlite3_close(database);
}

void Database::createClientsTable()
{
    const char *sqlQuery = "CREATE TABLE CLIENTS("  \
                           "ID INT NOT NULL," \
                           "NAME TEXT NOT NULL," \
                           "PASSWORD_HASH TEXT NOT NULL," \
                           "LOGIN TEXT," \
                           "PHONE TEXT," \
                           "EMAIL TEXT," \
                           "APPROVED INT );";
    char *errMsg;
    sqlite3_exec(database, sqlQuery, nullptr, nullptr, &errMsg);
}

void Database::createOperatorsTable()
{
    const char *sqlQuery = "CREATE TABLE OPERATORS("  \
                           "ID INT NOT NULL," \
                           "NAME TEXT NOT NULL," \
                           "PASSWORD_HASH TEXT NOT NULL," \
                           "LOGIN TEXT," \
                           "PHONE TEXT," \
                           "EMAIL TEXT);";
    char *errMsg;
    sqlite3_exec(database, sqlQuery, nullptr, nullptr, &errMsg);
}

void Database::createManagersTable()
{
    const char *sqlQuery = "CREATE TABLE MANAGERS("  \
                           "ID INT NOT NULL," \
                           "NAME TEXT NOT NULL," \
                           "PASSWORD_HASH TEXT NOT NULL," \
                           "LOGIN TEXT," \
                           "PHONE TEXT," \
                           "EMAIL TEXT);";
    char *errMsg;
    sqlite3_exec(database, sqlQuery, nullptr, nullptr, &errMsg);
}

void Database::createAdministratorsTable()
{

}

void Database::addClient(const Client &client)
{
    if (hasUser(client.getLogin()))
    {
        throw UserAlreadyExistsException();
    }

    std::string query = "INSERT INTO CLIENTS ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL,APPROVED) ";
    query += "VALUES (";
    query += std::to_string(client.getId()) + ", ";
    query += "\'" + client.getName() + "\', ";
    query += "\'" + client.getPasswordHash() + "\', ";
    query += "\'" + client.getLogin() + "\', ";
    query += "\'" + client.getPhone() + "\', ";
    query += "\'" + client.getEmail() + "\', ";
    query += "\'" + std::to_string(client.isApproved()) + "\'); ";

    char *errMsg;
    sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errMsg);
}

void Database::addManager(const Manager &manager)
{
    if (hasUser(manager.getLogin()))
    {
        throw UserAlreadyExistsException();
    }

    std::string query = "INSERT INTO MANAGERS ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL) ";
    query += "VALUES (";
    query += std::to_string(manager.getId()) + ", ";
    query += "\'" + manager.getName() + "\', ";
    query += "\'" + manager.getPasswordHash() + "\', ";
    query += "\'" + manager.getLogin() + "\', ";
    query += "\'" + manager.getPhone() + "\', ";
    query += "\'" + manager.getEmail() + "\');";

    char *errMsg;
    sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errMsg);
}

void Database::deleteUser(int64_t id)
{
    std::string query = "DELETE FROM CLIENTS WHERE ID = ";
    query += std::to_string(id) + ";";

    char *errMsg;
    sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errMsg);
}

static int hasUserCallbk(void *data, int numColumns, char **rowFields, char **columnNames)
{
    (void)numColumns;
    (void)columnNames;

    bool hasUser = atoi(rowFields[0]);
    *((bool *)data) = hasUser;

    return 0;
}

bool Database::hasUser(int64_t id)
{
    std::string query = "SELECT COUNT(1) FROM CLIENTS WHERE ID = \'" + std::to_string(id) + "\';";
    char *errMsg;
    bool result;
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    query = "SELECT COUNT(1) FROM OPERATORS WHERE ID = \'" + std::to_string(id) + "\';";
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    query = "SELECT COUNT(1) FROM MANAGERS WHERE ID = \'" + std::to_string(id) + "\';";
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    query = "SELECT COUNT(1) FROM ADMINISTRATORS WHERE ID = \'" + std::to_string(id) + "\';";
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    return false;
}

bool Database::hasUser(std::string login)
{
    std::string query = "SELECT COUNT(1) FROM CLIENTS WHERE LOGIN = \'" + login + "\';";
    char *errMsg;
    bool result;
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    query = "SELECT COUNT(1) FROM OPERATORS WHERE LOGIN = \'" + login + "\';";
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    query = "SELECT COUNT(1) FROM MANAGERS WHERE LOGIN = \'" + login + "\';";
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    query = "SELECT COUNT(1) FROM ADMINISTRATORS WHERE LOGIN = \'" + login + "\';";
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);
    if (result) { return true; }

    return false;
}

int64_t Database::generateUniqueUserId()
{
    int64_t id;

    do
    {
        id = rand() % 1000000;
    }
    while (hasUser(id));

    return id;
}

User *Database::getUserData(std::string login, std::string &type)
{
    type = "Client";

    User::Data data =
    {
        12345,
        "Example Examplovich",
        "+3-E-X-A-M-P-L-E",
        "example@example.com",
        "ada",
        HashComputer().hash("123")
    };
    Client *client = new Client(data);

    return client;
}
