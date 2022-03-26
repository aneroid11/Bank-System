#include <iostream>
#include <ctime>

#include "banksystemmodel.h"
#include "user.h"
#include "hashcomputer.h"
#include "database.h"
#include "dbnotopenedexception.h"
#include "useralreadyexistsexception.h"

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
    // Создаём пользователя. Пока просто создаём и добавляем в базу. Потом сделаем там поле approved,
    // которое будет показывать, подтвердил ли менеджер юзера.

    User::Data data =
    {
        database->generateUniqueUserId(),
        name,
        phone,
        email,
        login,
        HashComputer().hash(password)
    };

    User newUser(data);
    std::cout << "Добавление пользователя: " << name << "\n";

    database->addUser(newUser);
}
