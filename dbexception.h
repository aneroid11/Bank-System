#ifndef DBEXCEPTION_H
#define DBEXCEPTION_H

#include <exception>
#include <string>
#include <cstring>

class DBException : public std::exception
{
public:
    DBException(std::string errMsg) { errorMessage = errMsg; }

    DBException(const DBException &exc) { errorMessage = exc.errorMessage; }

    DBException &operator =(const DBException &other)
    {
        errorMessage = other.errorMessage;
        return *this;
    }

    const char *what() const noexcept { return strdup((std::string("Database error: ") + errorMessage).c_str()); }

private:
    std::string errorMessage;
};

#endif // DBEXCEPTION_H
