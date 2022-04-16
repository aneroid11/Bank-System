#include <cmath>
#include <iostream>

#include "account.h"
#include "constants.h"

Account::Account(int64_t id, std::string clientLogin, double initialBalance,
                 double percents, time_t creationTime, int st, Currency currencyType)
    : SomethingHoldingMoney(id, clientLogin, initialBalance, percents, creationTime, st, currencyType)
{
}

void Account::accumulate()
{
    // Вычислить новое значение баланса на основании того, сколько времени прошло с последнего начисления

    if (status != ACTIVE) { return; }

    time_t now = time(nullptr);
    time_t delta = now - creationTime;
    int monthsPassed = delta / SEC_IN_MONTH;
    double oneIterCoef = 1.0 + percents / 100.0;
    double newBalance = balance;

    if (monthsPassed < 1)
    {
        return;
    }

    for (int i = 0; i < monthsPassed; i++)
    {
        newBalance *= oneIterCoef;
    }

    balance = newBalance;

    //creationTime = time(nullptr);
    creationTime += monthsPassed * SEC_IN_MONTH;
}

std::string Account::getInfo() const
{
    std::string info;
    info += "ID: " + std::to_string(id) + "\n";
    info += "Принадлежит: " + clientLogin + "\n";
    info += "Баланс: " + std::to_string(balance);
    info += (currencyType == BYN ? " BYN" : " $");
    info += "\n";
    info += "Процентная ставка: " + std::to_string(percents) + "\n";
    info += "Последнее накопление по процентам: " + std::string(ctime(&creationTime));

    info += "Статус: ";

    switch (status) {
    case ACTIVE:
        info += "открыт\n";
        break;
    case CLOSED:
        info += "закрыт\n";
        break;
    case FROZEN:
        info += "заморожен\n";
        break;
    default:
        info  += "заблокирован\n";
    }
    return info;
}
