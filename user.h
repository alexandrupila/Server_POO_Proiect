#ifndef USER_H
#define USER_H

#include <QObject>
#include "auser.h"

class User
    : public AUser
{

public:
    User();
    User(const User& other);
    User(int user_id,QString username,QString email="default_mail",QString password="default_password",QString photo="");
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
    User operator=(User const& u)
    {
        return u;
    }
};

#endif // USER_H
