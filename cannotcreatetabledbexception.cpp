#include "cannotcreatetabledbexception.h"

const char *CannotCreateTableDBException::what() const noexcept
{
    return (std::string("Cannot create table: ") + errorMessage).c_str();
}
