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
#include "enterprise.h"
#include "credit.h"

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

std::list<Bank *> BankSystemModel::loadBanksList()
{
    std::list<Bank *> banks;

    banks.push_back(new Bank { "Банк 'Стеклянный'", 93209 });
    banks.push_back(new Bank { "Банк 'Оловянный'", 429049 });
    banks.push_back(new Bank { "Банк 'Деревянный'", 328948 });
    banksList = banks;
    return banks;
}

void BankSystemModel::setCurrentBank(std::string bankName)
{
    // найти этот банк в списке
    auto findIter = std::find_if(std::begin(banksList),
                                std::end(banksList),
                                [&](const Bank *b){ return b->name == bankName; });

    Bank *bank = findIter == banksList.end() ? nullptr : *findIter;
    setCurrentBank(bank);
}

void BankSystemModel::setCurrentBank(Bank *bank)
{
    // Генерируем хеш bankName и на его основе создаём файл с точкой в начале
    std::string fileName = std::string(".") + HashComputer().hash(bank->name) + ".db";

    if (database)
    {
        delete database;
        database = nullptr;
    }
    database = new Database(fileName);

    currentBank = bank;
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
                                                 std::string name, std::string phone, std::string passportData,
                                                 bool fromRB)
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

    Client newClient(data, passportData, fromRB);
    std::cout << "Добавление клиента: " << name << "\n";

    database->addClient(newClient);
}

void BankSystemModel::registerEnterprise(std::string type, std::string name, int64_t pan, int64_t bic, std::string address)
{
    if (!database) { throw DBNotOpenedException(); }

    Enterprise newEnterprise(database->generateUniqueId(), type, name, pan, bic, address);
    database->addEnterprise(newEnterprise);
}

void BankSystemModel::addSampleOperator()
{
    if (!database) { throw DBNotOpenedException(); }

    Operator::Data data =
    {
        database->generateUniqueUserId(),
        "Антонов Антон Антонович",
        "+333111111111",
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
        "Иванов Иван Иванович",
        "+372222222222",
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
        "Аркадьев Аркадий Аркадьевич",
        "+332222222222",
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

void BankSystemModel::openAccountForClient(Client *client, int *id)
{
    int accId = database->generateUniqueId();
    if (id != nullptr) { *id = accId; }

    Account account(accId,
                    client->getLogin(),
                    0.0, 2.4,
                    time(nullptr),
                    ACTIVE, client->isFromRB() ? BYN : US_DOLLAR);
    database->addAccount(account);
}

void BankSystemModel::openDepositForClient(Client *client, int termInMonths, double sum)
{
    std::cout << "BankSystemModel::openDepositForClient() for " << termInMonths << " months\n";

    Deposit deposit(database->generateUniqueId(), client->getLogin(),
                    sum, 10.0, time(nullptr), termInMonths, time(nullptr),
                    ACTIVE, client->isFromRB() ? BYN : US_DOLLAR);
    database->addDeposit(deposit);
}

std::list<Account *> BankSystemModel::getAllAccounts()
{
    return database->getAllAccounts();
}

std::list<Deposit *> BankSystemModel::getAllDeposits()
{
    return database->getAllDeposits();
}

std::list<Account *> BankSystemModel::getClientAccounts(Client *client)
{
    return database->getClientAccounts(client->getLogin());
}

std::list<Deposit *> BankSystemModel::getClientDeposits(Client *client)
{
    std::list<void *> records = database->getRecordsFromTableByParameter("DEPOSITS", "CLIENT_LOGIN", client->getLogin());
    std::list<Deposit *> deposits;

    for (void *r : records)
    {
        deposits.push_back((Deposit *)r);
    }
    return deposits;
}

std::list<Credit *> BankSystemModel::getClientCredits(Client *client)
{
    std::cout << "getClientCredits()\n";
    std::cout << client->getLogin() << "\n";
    std::list<void *> records = database->getRecordsFromTableByParameter("CREDITS", "CLIENT_LOGIN", client->getLogin());
    std::list<Credit *> credits;

    for (void *r : records)
    {
        std::cout << (int *)r << "\n";
        credits.push_back((Credit *)r);
    }
    return credits;
}

std::list<SomethingHoldingMoney *> BankSystemModel::getClientSmthHoldingMoneyByStatus(Client *client,
                                                                                      int requiredStatus,
                                                                                      std::string table)
{
    std::list<void *> records = database->getRecordsFromTableByParameter(table, "CLIENT_LOGIN", client->getLogin());
    std::list<SomethingHoldingMoney *> retList;

    for (void *r : records)
    {
        SomethingHoldingMoney *smth = (SomethingHoldingMoney *)r;

        if (smth->getStatus() == requiredStatus)
        {
            retList.push_back(smth);
        }
    }

    return retList;
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

std::list<Deposit *> BankSystemModel::getClientDepositsByStatus(Client *client, int requiredStatus)
{
    std::list<Deposit *> deposits = getClientDeposits(client);
    std::list<Deposit *> retDeposits;

    for (auto i = deposits.begin(); i != deposits.end(); i++)
    {
        Deposit *d = *i;

        if (d->getStatus() != requiredStatus)
        {
            delete d;
        }
        else
        {
            retDeposits.push_back(d);
        }
    }

    return retDeposits;
}

bool BankSystemModel::clientCanTakeLoan(std::string clientLogin, double loanValueUsd)
{
    // Получить все счета этого клиента
    std::string type;
    Client *client = (Client *)getUserData(clientLogin, type);
    std::list<Account *> accounts = getClientAccounts(client);

    double accountsValueUsd = 0.0;

    for (Account *a : accounts)
    {
        // учитываем только активные счета
        if (a->getStatus() == ACTIVE)
        {
            accountsValueUsd += CurrencyConverter().convert(a->getBalance(), a->getCurrencyType(), US_DOLLAR);
        }
    }

    bool result = accountsValueUsd >= loanValueUsd / 2;

    delete client;
    for (Account *a : accounts)
    {
        delete a;
    }

    return result;
}

SomethingHoldingMoney *BankSystemModel::getSomethingHoldingMoneyById(int64_t id, std::string *retTable)
{
    std::string tables[] = { "ACCOUNTS", "DEPOSITS" };

    for (std::string table : tables)
    {
        std::list<void *> arr = database->getRecordsFromTableByParameter(table, "ID", std::to_string(id));

        if (!arr.empty())
        {
            if (retTable) { *retTable = table; }
            return (SomethingHoldingMoney *)(*arr.begin());
        }
    }

    return nullptr;
}

Account *BankSystemModel::getAccountById(int64_t id)
{
    std::list<void *> accounts = database->getRecordsFromTableByParameter("ACCOUNTS",
                                                                          "ID",
                                                                          std::to_string(id));
    return (Account *)(*accounts.begin());
}

Deposit *BankSystemModel::getDepositById(int64_t id)
{
    std::list<void *> deposits = database->getRecordsFromTableByParameter("DEPOSITS",
                                                                          "ID",
                                                                          std::to_string(id));
    return (Deposit *)(*deposits.begin());
}

void BankSystemModel::setSmthHoldingMoneyStatus(int64_t id, int status)
{
    std::string table;
    SomethingHoldingMoney *something = getSomethingHoldingMoneyById(id, &table);
    something->setStatus(status);

    if (table == "ACCOUNTS")
    {
        updateAccountData((Account *)something);
    }
    else if (table == "DEPOSITS")
    {
        updateDepositData((Deposit *)something);
    }
    delete something;
}

void BankSystemModel::close(int64_t id)
{
    setSmthHoldingMoneyStatus(id, CLOSED);
}

void BankSystemModel::freeze(int64_t id)
{
    setSmthHoldingMoneyStatus(id, FROZEN);
}

void BankSystemModel::ban(int64_t id)
{
    setSmthHoldingMoneyStatus(id, BLOCKED);
}

void BankSystemModel::clientAccountAccumulate(int64_t id)
{
    Account *acc = getAccountById(id);
    acc->accumulate();
    updateAccountData(acc);
    delete acc;
}

void BankSystemModel::clientDepositCheckTerm(int64_t id)
{
    Deposit *dep = getDepositById(id);
    dep->checkTerm();
    updateDepositData(dep);
    delete dep;
}

void BankSystemModel::clientDepositAccumulate(int64_t id)
{
    Deposit *dep = getDepositById(id);
    dep->accumulate();
    updateDepositData(dep);
    delete dep;
}

void BankSystemModel::updateAccountData(Account *acc)
{
    database->updateAccount(acc);
}

void BankSystemModel::updateDepositData(Deposit *dep)
{
    database->updateDeposit(dep);
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

    CurrencyConverter converter;
    double putValue = converter.convert(value, senderAcc->getCurrencyType(), recipientAcc->getCurrencyType());

    senderAcc->withdrawMoney(value);
    recipientAcc->putMoney(putValue);

    database->updateAccount(senderAcc);
    database->updateAccount(recipientAcc);

    Transfer transfer(database->generateUniqueId(), sender, recipient, time(nullptr), value);
    database->addTransfer(transfer);

    delete senderAcc;
    delete recipientAcc;
}

void BankSystemModel::createCredit(int months, double value, Currency currency,
                                   double monthlyPercents, time_t creationTime, std::string clientLogin)
{
    Credit newCredit(database->generateUniqueId(), months, value, currency, monthlyPercents,
                     creationTime, creationTime, 0.0, clientLogin);
    database->addCredit(newCredit);

    std::string trash;
    Client *client = (Client *)database->getUserData(clientLogin, trash);

    int accId;
    openAccountForClient(client, &accId);
    putMoneyOnAccount(accId, newCredit.getValue());

    delete client;
}

void BankSystemModel::payCredit(int64_t id)
{
    std::cout << "need to pay for credit " << id << " here\n";

    std::list<void *> records = database->getRecordsFromTableByParameter("CREDITS", "ID", std::to_string(id));
    Credit *currCredit = (Credit *)(*records.begin());
    currCredit->pay();

    std::cout << currCredit->getInfo() << "\n";
    database->updateCredit(currCredit);
}
