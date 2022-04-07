#include <iostream>
#include <ctime>

#include "banksystemmodel.h"
#include "client.h"
#include "manager.h"
#include "administrator.h"
#include "hashcomputer.h"
#include "database.h"
#include "account.h"
#include "deposit.h"
#include "transfer.h"

#include "dbnotopenedexception.h"
#include "useralreadyexistsexception.h"
#include "wronguserpasswordexception.h"
#include "noaccountindbexception.h"

BankSystemModel::BankSystemModel()
{
    srand(time(nullptr));
}

BankSystemModel::~BankSystemModel()
{
    if (database)
    {
        delete database;
        database = nullptr;
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
        database = nullptr;
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

void BankSystemModel::addSampleOperator()
{
    if (!database) { throw DBNotOpenedException(); }

    Operator::Data data =
    {
        database->generateUniqueUserId(),
        "Example Examplovich Operator",
        "+3-E-X-A-M-P-L-E-2",
        "examp@example.com",
        "samplop",
        HashComputer().hash("123")
    };
    Operator newOperator(data);

    try
    {
        database->addOperator(newOperator);
    }
    catch (const UserAlreadyExistsException &)
    {
    }
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

void BankSystemModel::addSampleAdministrator()
{
    if (!database) { throw DBNotOpenedException(); }

    Administrator::Data data =
    {
        database->generateUniqueUserId(),
        "Example Admin",
        "+332424442424",
        "exa@exa.com",
        "sampladm",
        HashComputer().hash("123")
    };
    Administrator newAdm(data);

    try
    {
        database->addAdministrator(newAdm);
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

void BankSystemModel::approveClient(std::string login)
{
    if (!database) { throw DBNotOpenedException(); }
    database->approveClient(login);
}

std::list<Client *> BankSystemModel::getUnapprovedClients()
{
    if (!database) { throw DBNotOpenedException(); }

    return database->getUnapprovedClients();
}

void BankSystemModel::openAccountForClient(Client *client)
{
    Account account(database->generateUniqueId(), client->getLogin(), 0, 2.4, time(nullptr));
    database->addAccount(account);
}

void BankSystemModel::openDepositForClient(Client *client)
{
    Deposit deposit(database->generateUniqueId(), client->getLogin(), 0.0, 10.0, time(nullptr));
    database->addDeposit(deposit);
}

std::list<Account *> BankSystemModel::getClientAccounts(Client *client)
{
    return database->getClientAccounts(client->getLogin());
}

std::list<Account *> BankSystemModel::getClientAccountsByStatus(Client *client, int status)
{
    std::list<Account *> accounts = database->getClientAccounts(client->getLogin());
    std::list<Account *> retAccounts;

    for (auto i = accounts.begin(); i != accounts.end(); i++)
    {
        Account *a = *i;

        if (a->getStatus() != status)
        {
            delete a;
        }
        else
        {
            retAccounts.push_back(a);
        }
    }

    return retAccounts;
}

Account *BankSystemModel::getAccountById(int64_t id)
{
    std::list<void *> accounts = database->getRecordsFromTableByParameter("ACCOUNTS",
                                                                          "ID",
                                                                          std::to_string(id));
    return (Account *)(*accounts.begin());
}

void BankSystemModel::clientAccountAccumulate(int64_t id)
{
    std::list<void *> accounts = database->getRecordsFromTableByParameter("ACCOUNTS",
                                                                          "ID",
                                                                          std::to_string(id));
    Account *acc = (Account *)(*accounts.begin());
    acc->accumulate();
    updateAccountData(acc);
    delete acc;
}


void BankSystemModel::updateAccountData(Account *acc)
{
    database->updateAccount(acc);
}

void BankSystemModel::putMoneyOnAccount(int64_t id, double value)
{
    std::list<void *> accounts = database->getRecordsFromTableByParameter("ACCOUNTS",
                                                                          "ID",
                                                                          std::to_string(id));
    Account *acc = (Account *)(*accounts.begin());
    acc->putMoney(value);
    updateAccountData(acc);
    delete acc;

    std::cout << "put " << value << " amount of money on " << id << " account\n";
}

void BankSystemModel::withdrawMoneyFromAccount(int64_t id, double value)
{
    std::list<void *> accounts = database->getRecordsFromTableByParameter("ACCOUNTS",
                                                                          "ID",
                                                                          std::to_string(id));
    Account *acc = (Account *)(*accounts.begin());
    acc->withdrawMoney(value);
    updateAccountData(acc);
    delete acc;

    std::cout << "withdraw " << value << " amount of money from " << id << " account\n";
}

void BankSystemModel::createTransfer(int64_t sender, int64_t recipient, double value)
{
    // Создать перевод, записать в него данные, записать его в базу данных, перевести деньги со счёта на счёт
    Account *senderAcc = getAccountById(sender);
    Account *recipientAcc = getAccountById(recipient);

    if (!senderAcc || !recipientAcc)
    {
        throw NoAccountInDbException();
    }

    senderAcc->withdrawMoney(value);
    recipientAcc->putMoney(value);
    database->updateAccount(senderAcc);
    database->updateAccount(recipientAcc);

    Transfer transfer(database->generateUniqueId(), sender, recipient, time(nullptr), value);
    database->addTransfer(transfer);

    delete senderAcc;
    delete recipientAcc;
}
