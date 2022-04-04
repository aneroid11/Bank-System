#include "somethingholdingmoney.h"

SomethingHoldingMoney::SomethingHoldingMoney(int64_t id, int64_t initialBalance, double percents, time_t creationTime)
{
    this->id = id;
    this->balance = initialBalance;
    this->percents = percents;
    this->creationTime = creationTime;
}
