#include <iostream>

//#include <sqlite3.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

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
    /*std::string query = "SELECT COUNT(1) FROM CLIENTS WHERE ID = \'" + std::to_string(id) + "\';";
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
    if (result) { return true; }*/
    QSqlQuery checkQuery;

    QString tablesToCheck[] = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const QString &tableName : tablesToCheck)
    {
        checkQuery.prepare("SELECT COUNT(1) FROM :table WHERE ID = ':id';");
        checkQuery.bindValue(":table", tableName);
        checkQuery.bindValue(":id", std::to_string(id).c_str());
        if (checkQuery.exec() && checkQuery.next()) { return true; }
    }

    return false;
}

bool Database::hasUser(std::string login)
{
    //std::string query = "SELECT COUNT(1) FROM CLIENTS WHERE LOGIN = \'" + login + "\';";

    /*char *errMsg;
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
    if (result) { return true; }*/

    QSqlQuery checkQuery;

    QString tablesToCheck[] = { "CLIENTS", "OPERATORS", "MANAGERS", "ADMINISTRATORS" };

    for (const QString &tableName : tablesToCheck)
    {
        checkQuery.prepare("SELECT COUNT(1) FROM :table WHERE LOGIN = ':login';");
        checkQuery.bindValue(":table", tableName);
        checkQuery.bindValue(":login", login.c_str());
        if (checkQuery.exec() && checkQuery.next()) { return true; }
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

static int selectUsersCallback(void *data, int numColumns, char **rowFields, char **columnNames)
{
    //UserRawData *userRawData = (UserRawData *)data;
    UserRawData userRawData;

    for (int i = 0; i < numColumns; i++)
    {
        userRawData.columnNames.push_back(columnNames[i]);
        userRawData.rowFields.push_back(rowFields[i]);
    }

    std::list<UserRawData> &users = *((std::list<UserRawData> *)data);
    users.push_back(userRawData);

    return 0;
}

std::list<User *> Database::getUsersFromTableByParameter(std::string tableName,
                                                         std::string parameterName,
                                                         std::string parameterValue)
{
    /*std::string query = "SELECT * FROM ";
    query += tableName;
    query += " WHERE " + parameterName + " = \'" + parameterValue + "\';";
    char *errMsg;

    std::list<UserRawData> usersData;
    sqlite3_exec(database, query.c_str(), selectUsersCallback, &usersData, &errMsg);

    std::list<User *> users;

    for (const UserRawData& data : usersData)
    {
        //std::cout << data.columnNames[0] << " = " << data.rowFields[0] << "\n";
        users.push_back(createUserFromRawData(data, tableName));
    }*/
    QSqlQuery searchQuery;
    searchQuery.prepare("SELECT * FROM :table WHERE :parameterName = ':parameterValue';");
    searchQuery.bindValue(":table", tableName.c_str());
    searchQuery.bindValue(":parameterName", parameterName.c_str());
    searchQuery.bindValue(":parameterValue", parameterValue.c_str());

    std::list<User *> users;

    while (searchQuery.next())
    {
        const QSqlRecord &currRecord = searchQuery.record();

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

    okofskd;

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

    /*std::string query;
    char *errMsg;
    UserRawData userRawData;*/

    for (const std::string &tableName : tablesToCheck)
    {
        QSqlQuery getQuery;
        getQuery.prepare("SELECT * FROM :tableName WHERE LOGIN = ':login';");
        getQuery.bindValue(":tableName", tableName.c_str());
        getQuery.bindValue(":login", login.c_str());

        if (getQuery.exec() && getQuery.next())
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

        /*query = "SELECT * FROM";
        query += " " + tableName + " ";
        query += "WHERE LOGIN = \'" + login + "\';";

        sqlite3_exec(database, query.c_str(), getUserDataCallbk, (void *)&userRawData, &errMsg);

        if (userRawData.hasData())
        {
            type = tableName;
            return createUserFromRawData(userRawData, tableName);
        }*/
    }

    throw NoUserInDBException();
}
