#include <iostream>
#include <sstream>
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
#include "deposit.h"
#include "transfer.h"

#include "cannotopendbexception.h"
#include "useralreadyexistsexception.h"
#include "nouserindbexception.h"

Database::Database(std::string filename)
{
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
    createDepositsTable();
    createTransfersTable();
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
                  "PASSPORT_DATA TEXT," \
                  "FROM_RB INT," \
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
                  "BALANCE REAL," \
                  "PERCENT REAL," \
                  "CREATION_DATE INT," \
                  "STATUS INT);");
    query.exec();
}

void Database::createDepositsTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE DEPOSITS("  \
                  "ID INT NOT NULL," \
                  "CLIENT_LOGIN TEXT," \
                  "BALANCE REAL," \
                  "PERCENT REAL," \
                  "CREATION_DATE INT," \
                  "PERCENT_DATE INT," \
                  "TERM_IN_MONTHS INT," \
                  "STATUS INT);");
    query.exec();
}

void Database::createTransfersTable()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE TRANSFERS("  \
                  "ID INT NOT NULL," \
                  "SENDER_ID INT," \
                  "RECIPIENT_ID INT," \
                  "CREATION_DATE INT," \
                  "VALUE REAL);");
    query.exec();
}

void Database::addClient(const Client &client)
{
    if (hasUser(client.getLogin()) || hasUserWithPassportData(client.getPassportData()))
    {
        throw UserAlreadyExistsException();
    }

    std::string query = "INSERT INTO CLIENTS ";
    query += "(ID,NAME,PASSWORD_HASH,LOGIN,PHONE,EMAIL,PASSPORT_DATA,FROM_RB,APPROVED) ";
    query += "VALUES (";
    query += std::to_string(client.getId()) + ", ";
    query += "\'" + client.getName() + "\', ";
    query += "\'" + client.getPasswordHash() + "\', ";
    query += "\'" + client.getLogin() + "\', ";
    query += "\'" + client.getPhone() + "\', ";
    query += "\'" + client.getEmail() + "\', ";
    query += "\'" + client.getPassportData() + "\', ";
    query += "\'" + std::to_string(client.isFromRB()) + "\', ";
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

    query += "(ID, CLIENT_LOGIN, BALANCE, PERCENT, CREATION_DATE, STATUS) ";
    query += "VALUES (";
    query += std::to_string(account.getId()) + ", ";
    query += "\'" + account.getClientLogin() + "\', ";
    query += "\'" + std::to_string(account.getBalance()) + "\', ";
    query += "\'" + std::to_string(account.getPercents()) + "\', ";
    query += "\'" + std::to_string(account.getCreationTime()) + "\', ";
    query += "\'" + std::to_string(account.getStatus()) + "\'); ";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();

    std::cout << sqlQuery.lastError().text().toStdString() << "\n";
    // addSomethingHoldingMoney(account, "ACCOUNTS");
}

void Database::addDeposit(const Deposit &deposit)
{
    std::cout << "Need to add a deposit here for " << deposit.getClientLogin() << "\n";
    std::cout << "ID: " << deposit.getId() << "\n";

    if (hasRecord(deposit.getId()))
    {
        std::cout << "Already has such deposit\n";
        return;
    }

    std::string query = "INSERT INTO DEPOSITS ";

    query += "(ID, CLIENT_LOGIN, BALANCE, PERCENT, CREATION_DATE, PERCENT_DATE, TERM_IN_MONTHS, STATUS) ";
    query += "VALUES (";
    query += std::to_string(deposit.getId()) + ", ";
    query += "\'" + deposit.getClientLogin() + "\', ";
    query += "\'" + std::to_string(deposit.getBalance()) + "\', ";
    query += "\'" + std::to_string(deposit.getPercents()) + "\', ";
    query += "\'" + std::to_string(deposit.getCreationTime()) + "\', ";
    query += "\'" + std::to_string(deposit.getLastAccrualOfInterestTime()) + "\', ";
    query += "\'" + std::to_string(deposit.getTerm()) + "\', ";
    query += "\'" + std::to_string(deposit.getStatus()) + "\'); ";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(query.c_str());
    sqlQuery.exec();

    std::cout << sqlQuery.lastError().text().toStdString() << "\n";
}

void Database::addTransfer(const Transfer &transfer)
{
    if (hasRecord(transfer.getId()))
    {
        std::cout << "Already has such transfer\n";
        return;
    }

    /*
     *
    int64_t id;
    int64_t senderId, recipientId;
    time_t creationTime;
    double value;
     * */
    std::string query = "INSERT INTO TRANSFERS ";

    query += "(ID, SENDER_ID, RECIPIENT_ID, CREATION_DATE, VALUE) ";
    query += "VALUES (";
    query += std::to_string(transfer.getId()) + ", ";
    query += "\'" + std::to_string(transfer.getSenderId()) + "\', ";
    query += "\'" + std::to_string(transfer.getRecipientId()) + "\', ";
    query += "\'" + std::to_string(transfer.getCreationTime()) + "\', ";
    query += "\'" + std::to_string(transfer.getValue()) + "\');";

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

bool Database::hasUserWith(std::string parameterName, std::string parameterValue)
{
    QSqlQuery checkQuery;

    std::string tablesToCheck[] = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = "SELECT NAME FROM " + tableName +
                " WHERE " + parameterName + " = \'" + parameterValue + "\';";
        checkQuery.prepare(query.c_str());

        if (checkQuery.exec() && checkQuery.next())
        {
            std::cout << "has user\n";
            return true;
        }
    }

    return false;
}

bool Database::hasUser(int64_t id)
{
    return hasUserWith("ID", std::to_string(id));
    /*QSqlQuery checkQuery;

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

    return false;*/
}

bool Database::hasRecord(int64_t id)
{
    bool hasUserWithId = hasUser(id);

    if (hasUserWithId) { return true; }

    QSqlQuery checkQuery;
    std::string tablesToCheck[] = { "ACCOUNTS", "TRANSFERS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = std::string("SELECT ID FROM ") + tableName +
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
    return hasUserWith("LOGIN", login);
    /*QSqlQuery checkQuery;

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

    return false;*/
}

bool Database::hasUserWithPassportData(std::string passportData)
{
    return hasUserWith("PASSPORT_DATA", passportData);
    /*QSqlQuery checkQuery;

    std::string tablesToCheck[] = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const std::string &tableName : tablesToCheck)
    {
        std::string query = std::string("SELECT NAME FROM ") + tableName + " WHERE PASSPORT_DATA = \'" + passportData + "\';";
        checkQuery.prepare(query.c_str());

        if (checkQuery.exec() && checkQuery.next())
        {
            std::cout << "has user\n";
            return true;
        }
    }

    return false;*/
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
        std::string passwordData = query.value(rec.indexOf("PASSPORT_DATA")).toString().toStdString();
        bool fromRB = query.value(rec.indexOf("FROM_RB")).toBool();
        Client *client = new Client(userData, passwordData, fromRB);
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
        std::cout << "This is a record: deposit or account\n";

        // Это запись счёта или вклада
        int64_t id = query.value(rec.indexOf("ID")).toInt();

        QString clientLogin = query.value(rec.indexOf("CLIENT_LOGIN")).toString();

        QString initialBalanceStr = query.value(rec.indexOf("BALANCE")).toString();
        double initialBalance = initialBalanceStr.replace(',', '.').toDouble();

        QString percentStr = query.value(rec.indexOf("PERCENT")).toString();
        percentStr.replace(',', '.');

        double percents = percentStr.toDouble();

        time_t creationTime = query.value(rec.indexOf("CREATION_DATE")).toLongLong();

        int status = query.value(rec.indexOf("STATUS")).toInt();

        void *record = nullptr;

        if (tableName == "ACCOUNTS")
        {
            record = new Account(id,
                                 clientLogin.toStdString(),
                                 initialBalance,
                                 percents,
                                 creationTime,
                                 status,
                                 BYN);
        }
        else if (tableName == "DEPOSITS")
        {
            unsigned term = query.value(rec.indexOf("TERM_IN_MONTHS")).toInt();
            time_t percentTime = query.value(rec.indexOf("PERCENT_DATE")).toUInt();

            record = new Deposit(id,
                                 clientLogin.toStdString(),
                                 initialBalance,
                                 percents,
                                 creationTime,
                                 term,
                                 percentTime,
                                 status,
                                 BYN);
        }

        return record;
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
    std::list<void *> accountsRecords = getRecordsFromTableByParameter("ACCOUNTS", "CLIENT_LOGIN", clientLogin);
    std::list<Account *> accounts;

    for (void *a : accountsRecords)
    {
        accounts.push_back((Account *)a);
    }

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

void Database::updateAccount(Account *data)
{
    std::cout << "updating account: " << data->getId() << "\n";

    std::stringstream qs;
    qs << "UPDATE ACCOUNTS SET ";
    qs << "BALANCE = \'" << std::to_string(data->getBalance()) << "\', ";
    qs << "CREATION_DATE = \'" << std::to_string(data->getCreationTime()) << "\', ";
    qs << "STATUS = \'" << std::to_string(data->getStatus()) << "\' ";
    qs << "WHERE ID = \'" << std::to_string(data->getId()) << "\';";

    QSqlQuery sqlQuery;
    sqlQuery.prepare(qs.str().c_str());
    sqlQuery.exec();
}

void Database::updateDeposit(Deposit *data)
{
    std::cout << "updating deposit: " << data->getId() << "\n";
    std::cout << "status = " << data->getStatus() << "\n";

    std::stringstream qs;
    qs << "UPDATE DEPOSITS SET ";
    qs << "BALANCE = \'" << std::to_string(data->getBalance()) << "\', ";
    qs << "PERCENT_DATE = \'" << std::to_string(data->getLastAccrualOfInterestTime()) << "\', ";
    qs << "STATUS = \'" << std::to_string(data->getStatus()) << "\' ";
    qs << "WHERE ID = \'" << std::to_string(data->getId()) << "\';";
    // term не изменяется, creationDate не изменяется

    QSqlQuery sqlQuery;
    sqlQuery.prepare(qs.str().c_str());
    sqlQuery.exec();
}
