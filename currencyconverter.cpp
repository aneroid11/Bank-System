#include "currencyconverter.h"

CurrencyConverter::CurrencyConverter()
{
}

double CurrencyConverter::convert(double value, Currency valueCurrency, Currency outputCurrency)
{
    if (valueCurrency == outputCurrency)
    {
        return value;
    }

    if (valueCurrency == BYN)
    {
        return bynToUsd(value);
    }
    else
    {
        return usdToByn(value);
    }
}
