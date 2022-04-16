#include <iostream>
#include <cfloat>
#include <climits>
#include <cmath>

#include "deposit.h"
#include "constants.h"

Deposit::Deposit(int64_t id, std::string clientLogin, double initialBalance,
                 double percents, time_t creationTime, unsigned term,
                 time_t lastAccrualOfInterestTime, int status, Currency currencyType)
    : SomethingHoldingMoney(id, clientLogin, initialBalance, percents, creationTime, status, currencyType)
{
    this->term = term;
    this->lastAccrualOfInterestTime = lastAccrualOfInterestTime;
}

void Deposit::accumulate()
{
    // Вычислить новое значение баланса на основании того, сколько времени прошло с creationTime

    if (status != ACTIVE) { return; }

    time_t expireTime = creationTime + term * SEC_IN_MONTH;
    time_t now = time(nullptr);

    if (now > expireTime)
    {
        now = expireTime;
    }

    time_t delta = now - lastAccrualOfInterestTime;
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

    lastAccrualOfInterestTime += monthsPassed * SEC_IN_MONTH;
}

void Deposit::checkTerm()
{
    if (status != ACTIVE) { return; }

    // Если с даты создания вклада прошло больше месяцев, чем term, то вклад закрывается.
    time_t now = time(nullptr);
    time_t delta = now - creationTime;
    int monthsPassed = delta / SEC_IN_MONTH;

    if (monthsPassed > (int)term)
    {
        status = CLOSED;
    }
}

void Deposit::withdrawMoney(double value)
{
    checkTerm();

    // Вывести деньги можно только с закрытого счёта
    if (status != CLOSED) { return; }

    balance -= value;

    // Срок счёта истёк и все деньги с него сняты
    if (fabs(balance) < 0.01)
    {
        std::cout << "deleting deposit\n";
        status = DELETED;
    }

    std::cout << "status = " << status << "\n";
}

std::string Deposit::getInfo() const
{
    std::string info = SomethingHoldingMoney::getInfo();
    info += "Срок вклада: " + std::to_string(term) + " мес.\n";
    return info;
}
