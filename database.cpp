#include <iostream>

//#include <sqlite3.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

#include "database.h"
#include "hashcomputer.h"

#include "client.h"
#include "manager.h"

#include "cannotopendbexception.h"
#include "useralreadyexistsexception.h"
#include "nouserindbexception.h"

Database::Database(std::string filename)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(filename.c_str());

    if (!database.open())
    {
        //throw CannotOpenDBException(sqlite3_errmsg(database));
        throw CannotOpenDBException(database.lastError().text().toStdString());
    }

    createClientsTable();
    createOperatorsTable();
    createManagersTable();
    createAdministratorsTable();
}

Database::~Database()
{
    //sqlite3_close(database);
    if (database.isOpen())
    {
        database.close();
    }
}

void Database::createClientsTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE CLIENTS("  \
                  "ID INT NOT NULL," \
                  "NAME TEXT NOT NULL," \
                  "PASSWORD_HASH TEXT NOT NULL," \
                  "LOGIN TEXT," \
                  "PHONE TEXT," \
                  "EMAIL TEXT," \
                  "APPROVED INT );");
    query.exec();
}

void Database::createOperatorsTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE OPERATORS("  \
                  "ID INT NOT NULL," \
                  "NAME TEXT NOT NULL," \
                  "PASSWORD_HASH TEXT NOT NULL," \
                  "LOGIN TEXT," \
                  "PHONE TEXT," \
                  "EMAIL TEXT);");
    query.exec();
}

void Database::createManagersTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE MANAGERS("  \
                  "ID INT NOT NULL," \
                  "NAME TEXT NOT NULL," \
                  "PASSWORD_HASH TEXT NOT NULL," \
                  "LOGIN TEXT," \
                  "PHONE TEXT," \
                  "EMAIL TEXT);");
    query.exec();
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

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();
}

void Database::addManager(const Manager &manager)
{
    std::cout << "Adding manager: " << manager.getName() << "\n";

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

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();
}

void Database::deleteUser(int64_t id)
{
    std::string query = "DELETE FROM CLIENTS WHERE ID = ";
    query += std::to_string(id) + ";";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();
}

bool Database::hasUser(int64_t id)
{
    QSqlQuery checkQuery;

    std::string tablesToCheck[] = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = std::string("SELECT NAME FROM ") + tableName +
                " WHERE ID = \'" + std::to_string(id) + "\';";
        checkQuery.prepare(query.c_str());

        if (checkQuery.exec() && checkQuery.next())
        {
            std::cout << "has user\n";
            return true;
        }
    }

    return false;
}

bool Database::hasUser(std::string login)
{
    QSqlQuery checkQuery;

    std::string tablesToCheck[] = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = std::string("SELECT NAME FROM ") + tableName + " WHERE LOGIN = \'" + login + "\';";
        checkQuery.prepare(query.c_str());

        if (checkQuery.exec() && checkQuery.next())
        {
            std::cout << "has user\n";
            return true;
        }
    }

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

void Database::approveClient(std::string login)
{
    std::string query = "UPDATE CLIENTS SET APPROVED = 1 WHERE LOGIN = ";
    query += "\'" + login + "\'";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();
}

std::list<User *> Database::getUsersFromTableByParameter(std::string tableName,
                                                         std::string parameterName,
                                                         std::string parameterValue)
{
    std::string query = std::string("SELECT * FROM ") + tableName +
            " WHERE " + parameterName + " = \'" + parameterValue + "\';";

    QSqlQuery searchQuery;
    searchQuery.prepare(query.c_str());
    searchQuery.exec();

    const QSqlRecord rec = searchQuery.record();

    std::list<User *> users;

    while (searchQuery.next())
    {
        User::Data userData;
        userData.name = searchQuery.value(rec.indexOf("NAME")).toString().toStdString();
        userData.email = searchQuery.value(rec.indexOf("EMAIL")).toString().toStdString();
        userData.login = searchQuery.value(rec.indexOf("LOGIN")).toString().toStdString();
        userData.passwordHash = searchQuery.value(rec.indexOf("PASSWORD_HASH")).toString().toStdString();
        userData.phone = searchQuery.value(rec.indexOf("PHONE")).toString().toStdString();
        userData.id = searchQuery.value(rec.indexOf("ID")).toInt();

        if (tableName == "CLIENTS")
        {
            Client *client = new Client(userData);
            bool clientApproved = searchQuery.value(rec.indexOf("APPROVED")).toInt();

            if (clientApproved)
            {
                client->approve();
            }
            users.push_back(client);
        }
        else if (tableName == "MANAGERS")
        {
            Manager *manager = new Manager(userData);
            users.push_back(manager);
        }
    }

    return users;
}

std::list<Client *> Database::getUnapprovedClients()
{
    std::list<User *> unapproved = getUsersFromTableByParameter("CLIENTS", "APPROVED", "0");
    std::list<Client *> unapprovedClients;

    for (User *u : unapproved)
    {
        unapprovedClients.push_back((Client *)u);
    }

    std::cout << "unapprovedClients.size() = " << unapprovedClients.size() << "\n";
    return unapprovedClients;
}

User *Database::getUserData(std::string login, std::string &type)
{
    std::vector<std::string> tablesToCheck = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = std::string("SELECT * FROM ") + tableName + " WHERE LOGIN = \'" + login + "\';";
        QSqlQuery getQuery;
        getQuery.prepare(query.c_str());
        getQuery.exec();

        if (getQuery.next())
        {
            type = tableName;

            const QSqlRecord &currRecord = getQuery.record();
            User::Data userData;
            userData.name = currRecord.value(currRecord.indexOf("NAME")).toString().toStdString();
            userData.email = currRecord.value(currRecord.indexOf("EMAIL")).toString().toStdString();
            userData.login = currRecord.value(currRecord.indexOf("LOGIN")).toString().toStdString();
            userData.passwordHash = currRecord.value(currRecord.indexOf("PASSWORD_HASH")).toString().toStdString();
            userData.phone = currRecord.value(currRecord.indexOf("PHONE")).toString().toStdString();
            userData.id = currRecord.value(currRecord.indexOf("ID")).toInt();

            if (tableName == "CLIENTS")
            {
                Client *client = new Client(userData);
                bool clientApproved = currRecord.value(currRecord.indexOf("APPROVED")).toInt();

                if (clientApproved)
                {
                    client->approve();
                }
                return client;
            }
            if (tableName == "MANAGERS")
            {
                Manager *manager = new Manager(userData);
                return manager;
            }
        }
    }

    throw NoUserInDBException();
}
