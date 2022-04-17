#ifndef IINFORMING_H
#define IINFORMING_H

#include <string>

class IInforming
{
public:
    virtual ~IInforming() {}
    virtual std::string getInfo() const = 0;
};

#endif // IINFORMING_H
