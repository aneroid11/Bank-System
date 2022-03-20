#include "hashcomputer.h"

long long HashComputer::hash(const std::string& str)
{
    const int p = 31;
    const int m = 1e9 + 9;

    long long hashValue = 0;
    long long pPow = 1;

    for (char currSym : str)
    {
        hashValue = (hashValue + (currSym - 'a' + 1) * pPow) % m;
        pPow = (pPow * p) % m;
    }

    return hashValue;
}
