#include "credit.h"

#include <sstream>

double computePercentRate(int months)
{
    //3.0 - 2.0 * ((срок_кредита / 93.0)
    double percentsDelta = MAX_CREDIT_MONTH_PERCENTS - MIN_CREDIT_MONTH_PERCENTS;
    double percents = MAX_CREDIT_MONTH_PERCENTS;
    percents -= percentsDelta * (double)(months - MIN_MONTHS) / (MAX_MONTHS - MIN_MONTHS);

    return percents;
}

Credit::Credit(int64_t id, int months, double value, Currency currency,
               double monthlyPercents, time_t creationTime, double paidByClient, std::string clientLogin)
{
    this->id = id;
    this->months = months;
    this->value = value;
    this->currency = currency;
    this->monthlyPercents = monthlyPercents;
    this->creationTime = creationTime;
    this->paidByClient = paidByClient;
    this->clientLogin = clientLogin;
}

std::string Credit::getInfo() const
{
    std::stringstream inf;
    inf << "Информация о кредите:\n";
    inf << "ID: " << id << "\n";
    std::string currencyStr = currency == BYN ? "BYN" : "$";
    inf << "Сумма: " << value << " " << currencyStr << "\n";
    inf << "Процентная ставка (за месяц): " << monthlyPercents << "\n";
    inf << "Дата и время оформления" << ctime(&creationTime);
    inf << "Выплачено по кредиту: " << paidByClient << "\n";
    inf << "Клиент: " << clientLogin << "\n";
    return inf.str();
}
