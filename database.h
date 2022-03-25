#ifndef DATABASE_H
#define DATABASE_H

#include <string>

struct sqlite3;
class User;

class Database
{
public:
    Database(std::string filename = "users.db");
    ~Database();

    void createUserTable();
    void addUser(const User &user);
    void deleteUser(int64_t id);

private:
    sqlite3 *database;
};

#endif // DATABASE_H
