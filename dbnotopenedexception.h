#ifndef DBNOTOPENEDEXCEPTION_H
#define DBNOTOPENEDEXCEPTION_H

#include <exception>

class DBNotOpenedException : public std::exception
{
public:
    DBNotOpenedException() {}

    const char *what() const noexcept { return "Bank database was not opened so cannot be used"; }
};

#endif // DBNOTOPENEDEXCEPTION_H
