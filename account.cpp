#include <cmath>
#include <iostream>

#include "account.h"
#include "constants.h"

Account::Account(int64_t id, std::string clientLogin,
                 double initialBalance, double percents, time_t creationTime)
    : SomethingHoldingMoney(id, clientLogin, initialBalance, percents, creationTime)
{
}

void Account::accumulate()
{
    // Вычислить новое значение баланса на основании того, сколько времени прошло с creationTime

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
