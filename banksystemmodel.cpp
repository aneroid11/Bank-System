#include <iostream>

#include "banksystemmodel.h"
#include "hashcomputer.h"

void BankSystemModel::enter(const std::string &login, const std::string &password)
{
    const std::string passwordHash = HashComputer().hash(password);

    if (userIsInDatabase(login, passwordHash))
    {
        // Разослать событие входа в систему.
    }
    else
    {
        // здесь нужно придумать класс исключения.
        throw new std::exception();
    }
}

bool BankSystemModel::userIsInDatabase(const std::string& login, const std::string& passwordHash)
{
    (void)login;
    (void)passwordHash;
    return rand() % 2;
}
