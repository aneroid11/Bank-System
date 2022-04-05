#include <iostream>
#include <algorithm>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

#include "database.h"
#include "hashcomputer.h"

#include "client.h"
#include "manager.h"
#include "administrator.h"
#include "account.h"

#include "cannotopendbexception.h"
#include "useralreadyexistsexception.h"
#include "nouserindbexception.h"

Database::Database(std::string filename)
{
    //qDebug() << QSqlDatabase::drivers();
    database = QSqlDatabase::addDatabase("QSQLCIPHER");
    database.setDatabaseName(filename.c_str());

    if (!database.open())
    {
        //throw CannotOpenDBException(sqlite3_errmsg(database));
        throw CannotOpenDBException(database.lastError().text().toStdString());
    }

    QSqlQuery query;
    query.exec("PRAGMA key = 'not_key_for_db_encryption';");

    createClientsTable();
    createOperatorsTable();
    createManagersTable();
    createAdministratorsTable();
    createAccountsTable();
}

Database::~Database()
{
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
    QSqlQuery query;
    query.prepare("CREATE TABLE ADMINISTRATORS("  \
                  "ID INT NOT NULL," \
                  "NAME TEXT NOT NULL," \
                  "PASSWORD_HASH TEXT NOT NULL," \
                  "LOGIN TEXT," \
                  "PHONE TEXT," \
                  "EMAIL TEXT);");
    query.exec();
}

void Database::createAccountsTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE ACCOUNTS("  \
                  "ID INT NOT NULL," \
                  "CLIENT_LOGIN TEXT," \
                  "BALANCE INT," \
                  "PERCENT REAL," \
                  "CREATION_DATE INT);");
    query.exec();
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

void Database::addOperator(const Operator &op)
{
    if (hasUser(op.getLogin()))
    {
        throw UserAlreadyExistsException();
    }

    std::string query = "INSERT INTO OPERATORS ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL) ";
    query += "VALUES (";
    query += std::to_string(op.getId()) + ", ";
    query += "\'" + op.getName() + "\', ";
    query += "\'" + op.getPasswordHash() + "\', ";
    query += "\'" + op.getLogin() + "\', ";
    query += "\'" + op.getPhone() + "\', ";
    query += "\'" + op.getEmail() + "\');";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();
}

void Database::addAdministrator(const Administrator &admin)
{
    if (hasUser(admin.getLogin()))
    {
        throw UserAlreadyExistsException();
    }

    std::string query = "INSERT INTO ADMINISTRATORS ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL) ";
    query += "VALUES (";
    query += std::to_string(admin.getId()) + ", ";
    query += "\'" + admin.getName() + "\', ";
    query += "\'" + admin.getPasswordHash() + "\', ";
    query += "\'" + admin.getLogin() + "\', ";
    query += "\'" + admin.getPhone() + "\', ";
    query += "\'" + admin.getEmail() + "\');";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();
}

void Database::addAccount(const Account &account)
{
    if (hasRecord(account.getId()))
    {
        std::cout << "Already has such account\n";
        return;
    }

    std::string query = "INSERT INTO ACCOUNTS ";
    /*
     * ID, CLIENT_LOGIN, BALANCE, PERCENT, CREATION_DATE
     * */

    query += "(ID, CLIENT_LOGIN, BALANCE, PERCENT, CREATION_DATE) ";
    query += "VALUES (";
    query += std::to_string(account.getId()) + ", ";
    query += "\'" + account.getClientLogin() + "\', ";
    query += "\'" + std::to_string(account.getBalance()) + "\', ";
    query += "\'" + std::to_string(account.getPercents()) + "\', ";
    query += "\'" + std::to_string(account.getCreationTime()) + "\'); ";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();

    std::cout << sqlQuery.lastError().text().toStdString() << "\n";
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

bool Database::hasRecord(int64_t id)
{
    bool hasUserWithId = hasUser(id);

    if (hasUserWithId) { return true; }

    // Проверить таблицу со счетами
    QSqlQuery checkQuery;

    std::string tablesToCheck[] = { "ACCOUNTS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = std::string("SELECT NAME FROM ") + tableName +
                " WHERE ID = \'" + std::to_string(id) + "\';";
        checkQuery.prepare(query.c_str());

        if (checkQuery.exec() && checkQuery.next())
        {
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

int64_t Database::generateUniqueId()
{
    int64_t id;

    do
    {
        id = rand() % 1000000;
    }
    while (hasRecord(id));

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

User *Database::createUserFromData(const QSqlQuery &query, const QSqlRecord &rec, std::string tableName)
{
    User::Data userData;
    userData.name = query.value(rec.indexOf("NAME")).toString().toStdString();
    userData.email = query.value(rec.indexOf("EMAIL")).toString().toStdString();
    userData.login = query.value(rec.indexOf("LOGIN")).toString().toStdString();
    userData.passwordHash = query.value(rec.indexOf("PASSWORD_HASH")).toString().toStdString();
    userData.phone = query.value(rec.indexOf("PHONE")).toString().toStdString();
    userData.id = query.value(rec.indexOf("ID")).toInt();

    if (tableName == "CLIENTS")
    {
        Client *client = new Client(userData);
        bool clientApproved = query.value(rec.indexOf("APPROVED")).toInt();

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
    if (tableName == "ADMINISTRATORS")
    {
        Administrator *adm = new Administrator(userData);
        return adm;
    }
    if (tableName == "OPERATORS")
    {
        Operator *op = new Operator(userData);
        return op;
    }

    return nullptr;
}

void *Database::createRecordFromData(const QSqlQuery &query, const QSqlRecord &rec, std::string tableName)
{
    std::vector<std::string> userTableNames =
    {
        "ADMINISTRATORS", "OPERATORS", "MANAGERS", "CLIENTS"
    };

    if (std::count(userTableNames.begin(), userTableNames.end(), tableName))
    {
        // Это один из пользователей
        return createUserFromData(query, rec, tableName);
    }
    else
    {
        std::cout << "This is a record\n";

        // Это запись счёта
        int64_t newAccId = query.value(rec.indexOf("ID")).toInt();

        QString newAccClLogin = query.value(rec.indexOf("CLIENT_LOGIN")).toString();

        int64_t newAccInitialBalance = query.value(rec.indexOf("BALANCE")).toInt();

        QString percentStr = query.value(rec.indexOf("PERCENT")).toString();
        percentStr.replace(',', '.');

        double newAccPercents = percentStr.toDouble();

        time_t newAccCreationTime = query.value(rec.indexOf("CREATION_DATE")).toLongLong();

        Account *newAccount = new Account(newAccId, newAccClLogin.toStdString(), newAccInitialBalance, newAccPercents, newAccCreationTime);

        return newAccount;
    }

    return nullptr;
}

std::list<void *> Database::getRecordsFromTableByParameter(std::string tableName, std::string parameterName,
                                                           std::string parameterValue)
{
    std::string query = std::string("SELECT * FROM ") + tableName +
            " WHERE " + parameterName + " = \'" + parameterValue + "\';";
    QSqlQuery searchQuery;
    searchQuery.prepare(query.c_str());
    searchQuery.exec();
    const QSqlRecord rec = searchQuery.record();

    std::list<void *> records;

    while (searchQuery.next())
    {
        void *currRec = createRecordFromData(searchQuery, rec, tableName);
        records.push_back(currRec);
    }

    return records;
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
        User *currUser = createUserFromData(searchQuery, rec, tableName);
        users.push_back(currUser);
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

std::list<Account *> Database::getClientAccounts(std::string clientLogin)
{
    // Поиск в базе по таблице Accounts, чтобы найти счета, у которых совпадает поле client_login с параметром функции

    std::list<void *> accountsRecords = getRecordsFromTableByParameter("ACCOUNTS", "CLIENT_LOGIN", clientLogin);
    std::list<Account *> accounts;

    for (void *a : accountsRecords)
    {
        accounts.push_back((Account *)a);
    }

    std::cout << "accounts.size() = " << accounts.size() << "\n";

    return accounts;
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
            return createUserFromData(getQuery, currRecord, tableName);
        }
    }

    throw NoUserInDBException();
}
