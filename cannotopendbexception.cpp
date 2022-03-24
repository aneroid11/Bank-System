#include "cannotopendbexception.h"

CannotOpenDBException::CannotOpenDBException(std::string errMsg)
    : errorMsg(errMsg)
{
}

const char* CannotOpenDBException::what() const noexcept
{
    return (std::string("Cannot open database: ") + errorMsg).c_str();
}
