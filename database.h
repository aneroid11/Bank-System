#ifndef DATABASE_H
#define DATABASE_H

#include <string>

struct sqlite3;

class Database
{
public:
    Database(std::string filename = "users.db");
    ~Database();

    void createUserTable();

private:
    sqlite3 *database;
};

#endif // DATABASE_H
