#ifndef ERROREXCEPTION_H
#define ERROREXCEPTION_H

#include "exception.h"

class ErrorException : public Exception
{
public:
    ErrorException();
    const QString what() {}

};

#endif // ERROREXCEPTION_H
