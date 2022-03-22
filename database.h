#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

class Database
{
public:
    Database(std::string name);

private:
    std::string fileName;
};

#endif // DATABASE_H
