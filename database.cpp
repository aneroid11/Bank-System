#include <iostream>

#include <sqlite3.h>

#include "database.h"
#include "user.h"

#include "cannotopendbexception.h"
#include "useralreadyexistsexception.h"

Database::Database(std::string filename)
{
    if (sqlite3_open(filename.c_str(), &database))
    {
        throw CannotOpenDBException(sqlite3_errmsg(database));
    }

    createUserTable();
}

Database::~Database()
{
    sqlite3_close(database);
}

void Database::createUserTable()
{
    const char *sqlQuery = "CREATE TABLE USER("  \
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

void Database::addUser(const User &user)
{
    if (hasUser(user.getLogin()))
    {
        throw UserAlreadyExistsException();
    }

    std::string query = "INSERT INTO USER ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL,APPROVED) ";
    query += "VALUES (";
    query += std::to_string(user.getId()) + ", ";
    query += "\'" + user.getName() + "\', ";
    query += "\'" + user.getPasswordHash() + "\', ";
    query += "\'" + user.getLogin() + "\', ";
    query += "\'" + user.getPhone() + "\', ";
    query += "\'" + user.getEmail() + "\', ";
    query += "\'" + std::to_string(user.isApproved()) + "\'); ";

    char *errMsg;
    sqlite3_exec(database, query.c_str(), nullptr, nullptr, &errMsg);
}

void Database::deleteUser(int64_t id)
{
    std::string query = "DELETE FROM USER WHERE ID = ";
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
    std::string query = "SELECT COUNT(1) FROM USER WHERE ID = " + std::to_string(id) + ";";
    char *errMsg;
    bool result;
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);

    return result;
}

bool Database::hasUser(std::string login)
{
    std::string query = "SELECT COUNT(1) FROM USER WHERE LOGIN = \'" + login + "\';";
    char *errMsg;
    bool result;
    sqlite3_exec(database, query.c_str(), hasUserCallbk, (void *)&result, &errMsg);

    return result;
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
