#ifndef ARESPONSE_H
#define ARESPONSE_H

#include "iresponse.h"

class AResponse : public IResponse
{
public:
    AResponse();
protected:
    QJsonObject response;
};

#endif // ARESPONSE_H
