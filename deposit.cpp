#include "deposit.h"
#include "constants.h"

Deposit::Deposit(int64_t id, std::string clientLogin, double initialBalance,
                 double percents, time_t creationTime, unsigned term,
                 time_t lastAccrualOfInterestTime, int status)
    : SomethingHoldingMoney(id, clientLogin, initialBalance, percents, creationTime, status)
{
    this->term = term;
    this->lastAccrualOfInterestTime = lastAccrualOfInterestTime;
}

void Deposit::accumulate()
{
    // Вычислить новое значение баланса на основании того, сколько времени прошло с creationTime

    time_t now = time(nullptr);
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
