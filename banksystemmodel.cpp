#include <iostream>

#include "banksystemmodel.h"
#include "hashcomputer.h"

void BankSystemModel::enter(const std::string &login, const std::string &password)
{
    const std::string passwordHash = std::to_string(HashComputer().hash(password));

    if (!userIsInDatabase(login, passwordHash))
    {
        throw NoUserInDBException();
    }
}

bool BankSystemModel::userIsInDatabase(const std::string& login, const std::string& passwordHash) const
{
    (void)login;
    (void)passwordHash;
    return rand() % 2;
}
