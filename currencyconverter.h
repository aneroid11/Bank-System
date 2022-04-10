#ifndef CURRENCYCONVERTER_H
#define CURRENCYCONVERTER_H

enum Currency { BYN, US_DOLLAR };

class CurrencyConverter
{
public:
    CurrencyConverter();

    double convert(double value, Currency valueCurrency, Currency outputCurrency);

private:
    double bynToUsd(double byn) { return byn / 3.0; }
    double usdToByn(double usd) { return usd * 3.0; }
};

#endif // CURRENCYCONVERTER_H
