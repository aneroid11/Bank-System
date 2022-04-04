#include "account.h"

Account::Account(int64_t id, std::string clientLogin,
                 int64_t initialBalance, double percents, time_t creationTime)
    : SomethingHoldingMoney(id, clientLogin, initialBalance, percents, creationTime)
{
}
