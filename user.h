#ifndef USER_H
#define USER_H

#include <QObject>
#include "iserializable.h"

class User
    : public ISerializable
{
private:
    int id;
    QString username;
    QString email;
    QString password;
    //QVector<IChat*> chat_list;
    //team_list
    //chat_list
    //assignment_list??
    //photo
public:
    User();
    User(const User& other);
    User(int user_id,QString username,QString email,QString password)
        : id(user_id), username(username), email(email),password(password) {}
    QJsonDocument serialize() override;
    void deserialize(QJsonObject& receivedObj) override;
    QString getUsername() {return username;}
    QString getEmail() {return email;}
    QString getPassword(){return password;}
    int getId() {return this->id;}
};

#endif // USER_H
