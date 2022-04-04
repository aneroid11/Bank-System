#ifndef SOMETHINGHOLDINGMONEY_H
#define SOMETHINGHOLDINGMONEY_H

#include <cstdlib>
#include <ctime>

class SomethingHoldingMoney
{
public:
    SomethingHoldingMoney(int64_t id, int64_t initialBalance, double percents, time_t creationTime);

    int64_t getId() const { return id; }
    int64_t getBalance() const { return balance; }
    double getPercents() const { return percents; }
    time_t getCreationTime() const { return creationTime; }

protected:
    int64_t id;
    int64_t balance;
    double percents;
    time_t creationTime;
};

#endif // SOMETHINGHOLDINGMONEY_H
