#ifndef ERROREXCEPTION_H
#define ERROREXCEPTION_H

#include "exception.h"

class ErrorException : public Exception
{
public:
    ErrorException();
    const char* what() const _GLIBCXX_USE_NOEXCEPT;
};

#endif // ERROREXCEPTION_H
