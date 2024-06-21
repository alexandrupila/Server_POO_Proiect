#include "auser.h"

AUser::AUser() {}

QString AUser::getUsername()
{
    return this->username;
}

QString AUser::getEmail()
{
    return this->email;
}

QString AUser::getPassword()
{
    return this->password;
}

QString AUser::getPhoto()
{
    return this->base64photo;
}

int AUser::getId()
{
    return this->id;
}

void AUser::setId(int id)
{
    this->id=id;
}

void AUser::setUsername(QString name)
{
    this->username=name;
}
