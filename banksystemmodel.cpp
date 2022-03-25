#include <iostream>
#include <ctime>

#include "banksystemmodel.h"
#include "hashcomputer.h"
#include "database.h"

BankSystemModel::BankSystemModel()
{
    srand(time(nullptr));

    database = new Database("data.db");
}

BankSystemModel::~BankSystemModel()
{
    delete database;
}

void BankSystemModel::enter(const std::string &login, const std::string &password)
{
    //const std::string passwordHash = HashComputer().hash(password);

    if (!database->hasUser(login))
    {
        throw NoUserInDBException();
    }
}
