#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include <QObject>
#include <QtSql>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include "user.h"
#include "ichat.h"

class QueryHandler
{
private:
    QSqlDatabase db;
    static QueryHandler* instance;
    QueryHandler();
    ~QueryHandler() {};
public:
    static QueryHandler& getInstance();
    static void destroyInstance();
    QVariantList queryDB(QSqlQuery query);
    User retrieveNewUser(QString email);
    void insertUser(User new_user);
    bool userExists(const QString& email, const QString& username, const QString& password);
    bool checkCredentials(const QString& email,const QString& password);
    User retrieveUser(int id_user);
    void updateUser(User updated_user);
    QVector<IChat*> retrieveChats(int id_user);
    bool directMessageChatExists(int user1_id,int user2_id);
    int createDirectMessageChat(int creator_id,QString chat_name);
    void addUserToChat(int chat_id,int user_id);
    int getUserId(QString username);
    void updateUserChats(QString new_username);
};

#endif // QUERYHANDLER_H
