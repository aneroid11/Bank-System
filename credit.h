#ifndef CREDIT_H
#define CREDIT_H

const double MIN_CREDIT_VALUE = 100.0;
const double MAX_CREDIT_VALUE = 10000.0;

const double MAX_CREDIT_MONTH_PERCENTS = 3.0;
const double MIN_CREDIT_MONTH_PERCENTS = 1.0;

const int MAX_MONTHS = 96;
const int MIN_MONTHS = 3;

double computePercentRate(int months);

class Credit
{
public:
    Credit();
};

#endif // CREDIT_H
