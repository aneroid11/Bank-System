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

    void addUser(const User &user);
    void deleteUser(int64_t id);
    bool hasUser(int64_t id);
    bool hasUser(std::string login);

    //void approveUser(std::string login);

    int64_t generateUniqueUserId();

private:
    void createUserTable();

    sqlite3 *database;
};

#endif // DATABASE_H
