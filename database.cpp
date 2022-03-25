#include <iostream>

#include <sqlite3.h>

#include "database.h"
#include "user.h"

#include "cannotopendbexception.h"

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
                           "ID INT PRIMARY KEY NOT NULL," \
                           "NAME TEXT NOT NULL," \
                           "PASSWORD_HASH TEXT NOT NULL," \
                           "LOGIN TEXT," \
                           "PHONE TEXT," \
                           "EMAIL TEXT );";
    char *errMsg;
    sqlite3_exec(database, sqlQuery, nullptr, nullptr, &errMsg);
}

void Database::addUser(const User &user)
{
    std::string query = "INSERT INTO USER ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL) ";
    query += "VALUES (";
    query += std::to_string(user.getId()) + ", ";
    query += "\'" + user.getName() + "\', ";
    query += "\'" + user.getPasswordHash() + "\', ";
    query += "\'" + user.getLogin() + "\', ";
    query += "\'" + user.getPhone() + "\', ";
    query += "\'" + user.getEmail() + "\'); ";

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

/*
#include <iostream>
#include <string>
#include <cstdlib>

#include <sqlite3.h>

static int selectCallback(void *data, int numColumns, char **rowFields, char **columnNames) {
    (void)data;

    int i;

    for (i = 0; i < numColumns; i++) {
        std::cout << columnNames[i] << " == " << (rowFields[i] ? rowFields[i] : "NULL") << "\n";
    }

    printf("\n");
    return 0;
}

void addTable(sqlite3 *db)
{
    const char *sqlQuery = "CREATE TABLE COMPANY("  \
                           "ID INT PRIMARY KEY     NOT NULL," \
                           "NAME           TEXT    NOT NULL," \
                           "AGE            INT     NOT NULL," \
                           "ADDRESS        CHAR(50)," \
                           "SALARY         REAL );";
    char *errMsg;

    if (sqlite3_exec(db, sqlQuery, nullptr, nullptr, &errMsg)){
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

sqlite3* createDatabase(std::string filename)
{
    sqlite3 *db;

    if (sqlite3_open(filename.c_str(), &db)) {
        return nullptr;
    }

    addTable(db);
    return db;
}

int main() {
    sqlite3 *db;

    if (!(db = createDatabase("test.db")))
    {
        std::cerr << "Terminating the program\n";
        return 1;
    }

    char *zErrMsg = 0;
    const char *sqlQuery = "SELECT * FROM COMPANY;";

    if (sqlite3_exec(db, sqlQuery, selectCallback, nullptr, &zErrMsg)) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);

    return 0;
}*/

