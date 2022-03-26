#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "user.h"

class Administrator : public User
{
public:
    Administrator(const Data &data);
};

#endif // ADMINISTRATOR_H
