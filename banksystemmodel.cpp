#include <iostream>
#include <ctime>

#include "banksystemmodel.h"
#include "client.h"
#include "manager.h"
#include "hashcomputer.h"
#include "database.h"

#include "dbnotopenedexception.h"
#include "useralreadyexistsexception.h"
#include "wronguserpasswordexception.h"

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

void BankSystemModel::test()
{
    database->getUsersFromTableByParameter("CLIENTS", "APPROVED", "0");
    std::cout << "End of test\n";
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
    if (!database) { throw DBNotOpenedException(); }

    std::string userType;
    // getUserData() выкинет исключение об отсутствии пользователя, если пользователя
    // нет в базе
    User *user = database->getUserData(login, userType);

    // если юзер существует, то проверить правильность введённого пароля
    // и если он неправильный, то выкинуть исключение
    std::string passwordHash = HashComputer().hash(password);

    if (passwordHash != user->getPasswordHash())
    {
        throw WrongUserPasswordException();
    }
}

void BankSystemModel::sendSignupRequestForClient(std::string login, std::string password, std::string email,
                                                 std::string name, std::string phone)
{
    if (!database) { throw DBNotOpenedException(); }

    Client::Data data =
    {
        database->generateUniqueUserId(),
        name,
        phone,
        email,
        login,
        HashComputer().hash(password)
    };

    Client newClient(data);
    std::cout << "Добавление клиента: " << name << "\n";

    database->addClient(newClient);
}

void BankSystemModel::addSampleManager()
{
    if (!database) { throw DBNotOpenedException(); }

    Manager::Data data =
    {
        database->generateUniqueUserId(),
        "Example Examplovich",
        "+3-E-X-A-M-P-L-E",
        "example@example.com",
        "samplman",
        HashComputer().hash("123")
    };
    Manager newManager(data);

    try
    {
        database->addManager(newManager);
    }
    catch (const UserAlreadyExistsException &)
    {
    }
}

User *BankSystemModel::getUserData(std::string login, std::string &type)
{
    if (!database) { throw DBNotOpenedException(); }

    return database->getUserData(login, type);
}

std::list<Client *> BankSystemModel::getUnapprovedClients()
{
    if (!database) { throw DBNotOpenedException(); }

    return database->getUnapprovedClients();
}
