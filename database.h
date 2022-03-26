#ifndef DATABASE_H
#define DATABASE_H

#include <string>

struct sqlite3;
class Client;

class Database
{
public:
    Database(std::string filename);
    ~Database();

    void addClient(const Client &client);

    void deleteUser(int64_t id);
    bool hasUser(int64_t id);
    bool hasUser(std::string login);

    //void approveClient(std::string login);

    int64_t generateUniqueUserId();

private:
    void createClientsTable();

    sqlite3 *database;
};

#endif // DATABASE_H
