#include "deposit.h"

Deposit::Deposit(int64_t id, std::string clientLogin, double initialBalance,
                 double percents, time_t creationTime, int status)
    : SomethingHoldingMoney(id, clientLogin, initialBalance, percents, creationTime, status)
{
}
