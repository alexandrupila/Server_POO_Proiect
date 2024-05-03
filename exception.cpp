#include "exception.h"

Exception::Exception(const QString &message)
{
    this->message = message;
}

Exception::~Exception() _GLIBCXX_USE_NOEXCEPT
{
    // do nothing
}

void Exception::raise() const
{
    throw *this;
}

Exception * Exception::clone() const
{
    return new Exception(*this);
}

const QString Exception::what() const _GLIBCXX_USE_NOEXCEPT
{
    return message;
}
