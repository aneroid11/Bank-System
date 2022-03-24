#include <iostream>

#include "banksystemmodel.h"
#include "hashcomputer.h"

void BankSystemModel::enter(const std::string &login, const std::string &password)
{
    const std::string passwordHash = HashComputer().hash(password);

    if (!userIsInDatabase(login, passwordHash))
    {
        throw NoUserInDBException();
    }
}

bool BankSystemModel::userIsInDatabase(const std::string& login, const std::string& passwordHash) const
{
    // Найти информацию о пользователе в базе данных. Если её там нет, вернуть false.
    (void)login;
    (void)passwordHash;
    return rand() % 2;
}
