#ifndef IUSER_H
#define IUSER_H

#include "iserializable.h"

class IUser : public ISerializable
{
public:
    IUser();
    virtual QString getUsername()=0;
    virtual QString getEmail()=0;
    virtual QString getPassword()=0;
    virtual QString getPhoto()=0;
    virtual int getId()=0;
    virtual void setId(int id)=0;
    virtual void setUsername(QString name)=0;
};

#endif // IUSER_H
