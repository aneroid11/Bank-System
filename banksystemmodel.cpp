#include <iostream>
#include <ctime>

#include "banksystemmodel.h"
#include "hashcomputer.h"
#include "database.h"
#include "dbnotopenedexception.h"

BankSystemModel::BankSystemModel()
{
    srand(time(nullptr));
}

BankSystemModel::~BankSystemModel()
{
    if (database)
    {
        delete database;
    }
}

void BankSystemModel::setCurrentBank(std::string bankName)
{
    // Генерируем хеш bankName и на его основе создаём файл с точкой в начале
    std::string fileName = std::string(".") + HashComputer().hash(bankName) + ".db";

    if (database)
    {
        delete database;
    }
    database = new Database(fileName);
}

void BankSystemModel::enter(std::string login, std::string password)
{
    if (!database)
    {
        throw DBNotOpenedException();
    }
    //const std::string passwordHash = HashComputer().hash(password);

    if (!database->hasUser(login))
    {
        throw NoUserInDBException();
    }
}

void BankSystemModel::sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                                 std::string name, std::string phone)
{

    //std::cout << name << ": юзер отправил запрос на регистрацию\n";
}
