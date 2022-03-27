#include <iostream>

#include <sqlite3.h>

#include "database.h"
#include "hashcomputer.h"

#include "client.h"
#include "manager.h"

#include "cannotopendbexception.h"
#include "useralreadyexistsexception.h"
#include "nouserindbexception.h"

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

static int selectUsersCallback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

std::list<User *> Database::getUsersFromTableByParameter(std::string tableName,
                                                         std::string parameterName,
                                                         std::string parameterValue)
{
   std::string query = "SELECT * FROM ";
    query += tableName;
    query += " WHERE " + parameterName + " = \'" + parameterValue + "\';";
    char *errMsg;

    sqlite3_exec(database, query.c_str(), selectUsersCallback, (void*)"Callback func called", &errMsg);

    return std::list<User *>();
}

std::list<Client *> Database::getUnapprovedClients()
{
    std::list<User *> unapproved = getUsersFromTableByParameter("CLIENTS", "APPROVED", "0");
    std::list<Client *> unapprovedClients;

    for (User *u : unapproved)
    {
        unapprovedClients.push_back((Client *)u);
    }

    return unapprovedClients;
}

static int getUserDataCallbk(void *data, int numColumns, char **rowFields, char **columnNames)
{
    UserRawData *userRawData = (UserRawData *)data;

    for (int i = 0; i < numColumns; i++)
    {
        userRawData->columnNames.push_back(columnNames[i]);
        userRawData->rowFields.push_back(rowFields[i]);
    }

    return 0;
}

User *Database::createUserFromRawData(const UserRawData& data, std::string type)
{
    User::Data userData;

    userData.id = atoi(data.rowFields[0].c_str());
    userData.name = data.rowFields[1];
    userData.passwordHash = data.rowFields[2];
    userData.login = data.rowFields[3];
    userData.phone = data.rowFields[4];
    userData.email = data.rowFields[5];

    if (type == "CLIENTS")
    {
        Client *client = new Client(userData);
        bool clientApproved = atoi(data.rowFields[6].c_str());

        if (clientApproved)
        {
            client->approve();
        }
        return client;
    }
    if (type == "MANAGERS")
    {
        Manager *manager = new Manager(userData);
        return manager;
    }

    return nullptr;
}

User *Database::getUserData(std::string login, std::string &type)
{
    std::vector<std::string> tablesToCheck = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    std::string query;
    char *errMsg;
    UserRawData userRawData;

    for (const std::string &tableName : tablesToCheck)
    {
        query = "SELECT * FROM";
        query += " " + tableName + " ";
        query += "WHERE LOGIN = \'" + login + "\';";

        sqlite3_exec(database, query.c_str(), getUserDataCallbk, (void *)&userRawData, &errMsg);

        if (userRawData.hasData())
        {
            type = tableName;
            return createUserFromRawData(userRawData, tableName);
        }
    }

    throw NoUserInDBException();
}
