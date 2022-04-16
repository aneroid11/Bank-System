#include "credit.h"

double computePercentRate(int months, double value)
{
    //3.0 - 2.0 * ((срок_кредита / 93.0) * (сумма_кредита / (maxValue - minValue)))
    double percentsDelta = MAX_CREDIT_MONTH_PERCENTS - MIN_CREDIT_MONTH_PERCENTS;
    double percents = MAX_CREDIT_MONTH_PERCENTS;
    percents -= percentsDelta * ((double)months / (MAX_MONTHS - MIN_MONTHS) * (value / (MAX_CREDIT_VALUE - MIN_CREDIT_VALUE)));

    return percents;
}

Credit::Credit()
{

}
