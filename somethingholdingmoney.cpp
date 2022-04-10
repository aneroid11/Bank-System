#include "somethingholdingmoney.h"

SomethingHoldingMoney::SomethingHoldingMoney(int64_t id, std::string clientLogin, double initialBalance,
                                             double percents, time_t creationTime, int status, Currency currencyType)
{
    this->id = id;
    this->clientLogin = clientLogin;
    this->balance = initialBalance;
    this->percents = percents;
    this->creationTime = creationTime;
    this->status = status;
    this->currencyType = currencyType;
}
