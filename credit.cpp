#include "credit.h"
#include "constants.h"

#include <cmath>
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
               double monthlyPercents, time_t creationTime, time_t lastPaymentTime,
               double paidByClient, std::string clientLogin)
{
    this->id = id;
    this->months = months;
    this->value = value;
    this->currency = currency;
    this->monthlyPercents = monthlyPercents;
    this->creationTime = creationTime;
    this->lastPaymentTime = lastPaymentTime;
    this->paidByClient = paidByClient;
    this->clientLogin = clientLogin;
}

double Credit::getAmountOfMoneyClientMustPay() const
{
    //сумма_кредита * (1 + p)^срок_кредита
    return value * pow((1 + monthlyPercents / 100.0), months);
}

double Credit::getMonthlyPayment() const
{
    return getAmountOfMoneyClientMustPay() / months;
}

int Credit::getMonthsFromLastPaymentTime() const
{
    time_t now = time(nullptr);
    time_t elapsed = now - lastPaymentTime;
    int monthsElapsed = elapsed / SEC_IN_MONTH;
    return monthsElapsed;
}

double Credit::getPaymentFromLastPaymentTime() const
{
    return getMonthsFromLastPaymentTime() * getMonthlyPayment();
}

void Credit::pay()
{
    paidByClient += getPaymentFromLastPaymentTime();
    lastPaymentTime += getMonthsFromLastPaymentTime() * SEC_IN_MONTH;
}

std::string Credit::getInfo() const
{
    std::stringstream inf;
    inf << "Информация о кредите:\n";
    inf << "ID: " << id << "\n";
    inf << "Срок кредита: " << months << " месяцев\n";
    std::string currencyStr = currency == BYN ? "BYN" : "$";
    inf << "Сумма: " << value << " " << currencyStr << "\n";
    inf << "Процентная ставка (за месяц): " << monthlyPercents << " %\n";
    inf << "Дата и время оформления: " << ctime(&creationTime);
    inf << "Дата и время последнего платежа по кредиту: " << ctime(&lastPaymentTime);
    inf << "Выплачено по кредиту: " << paidByClient << "\n";
    inf << "Клиент: " << clientLogin << "\n";

    inf << "Статус: ";

    if (paidByClient >= getAmountOfMoneyClientMustPay() - 0.01)
    {
        inf << "погашен\n";
    }
    else
    {
        inf << "не погашен\n";
    }

    return inf.str();
}
