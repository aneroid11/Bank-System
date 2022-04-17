#ifndef MANAGER_H
#define MANAGER_H

#include "operator.h"

class Manager : public Operator
{
public:
    Manager(const Data &data);
};

#endif // MANAGER_H
