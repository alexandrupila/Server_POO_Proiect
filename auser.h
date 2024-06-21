#ifndef AUSER_H
#define AUSER_H

#include "iuser.h"

class AUser : public IUser
{
public:
    AUser();
    virtual QString getUsername() override;
    virtual QString getEmail() override;
    virtual QString getPassword() override;
    virtual QString getPhoto() override;
    virtual int getId() override;
    virtual void setId(int id) override;
    virtual void setUsername(QString name) override;
protected:
    int id;
    QString username;
    QString email;
    QString password;
    QString base64photo;
};

#endif // AUSER_H
