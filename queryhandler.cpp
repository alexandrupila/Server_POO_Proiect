#include "queryhandler.h"
#include "groupchat.h"
#include "directmessagechat.h"
#include "filemessage.h"

QueryHandler* QueryHandler::instance=nullptr;

QueryHandler::QueryHandler()
{
    QString serverName = "DESKTOP-JBOB4F7\\SQLEXPRESS";
    QString dbName = "ATMTeams_DB";
    db=QSqlDatabase::addDatabase("QODBC");
    QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;Trusted_Connection=yes;").arg(serverName).arg(dbName);
    db.setDatabaseName(dsn);

    if (db.open()) {

        qDebug() << "Conexiunea la baza de date a fost stabilita cu succes!";
    } else {
        qDebug()<<db.lastError();
        qDebug() << "Eroare la conectarea la baza de date";
    }
}

QueryHandler &QueryHandler::getInstance()
{
    if(instance==nullptr)
    {
        instance= new QueryHandler();
        return *instance;
    }
    else return *instance;
}

void QueryHandler::destroyInstance()
{
    if(instance==nullptr) return;
    else
    {
        delete instance;
        instance=nullptr;
    }
}

QVariantList QueryHandler::queryDB(QSqlQuery query)
{
    QVariantList result;

    if(query.exec())
    {
        while(query.next())
        {
            QMap<QString,QVariant> row;
            for(int i=0;i<query.record().count();i++)
            {
                row[query.record().fieldName(i)]=query.value(i);
                result<<row.value(query.record().fieldName(i));
            }
            qDebug()<<row;
        }
    }
    else qDebug()<<"Database query failed."<<query.lastError().text();

    return result;

}

User QueryHandler::retrieveNewUser(QString email)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM Users WHERE email = :email");

    query.bindValue(":email", email);

    QVariantList result = queryDB(query);

        int user_id = result.value(0).toInt();
        QString username = result.value(1).toString();
        QString password = result.value(2).toString();
        QString email_user = result.value(4).toString();

        return User(user_id, username, email_user,password);
}

void QueryHandler::insertUser(User new_user)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Users (username, password, email) VALUES (:username, :password, :email)");

    query.bindValue(":username", new_user.getUsername());
    query.bindValue(":password", new_user.getPassword());
    query.bindValue(":email", new_user.getEmail());


    QVariantList result = queryDB(query);

    if (!result.isEmpty()) {
        qDebug() << "User inserted successfully!";
    } else {
        qDebug() << "Error inserting user:" << query.lastError().text();
    }
}

bool QueryHandler::userExists(const QString &email, const QString &username, const QString &password)
{
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM Users WHERE email = :email AND username = :username AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":username", username);

    QVariantList result=this->queryDB(query);

    if(result.value(0).toInt()==0)
    {
        qDebug()<<"user does not exist";
        return 0;
    }

    return 1;
}

bool QueryHandler::checkCredentials(const QString &email, const QString &password)
{
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) AS nr_users FROM Users WHERE email = :email AND password = :password");

    query.bindValue(":email", email);
    query.bindValue(":password", password);

    QVariantList result = queryDB(query);

    if (result.value(0).toInt()>0) {

        return 1;
    } else {
        qDebug() << "Error checking credentials:" << query.lastError().text();
        return 0;
    }

}

User QueryHandler::retrieveUser(int id)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE user_id= :user_id");

    query.bindValue(":user_id",id);

    QVariantList result =this->queryDB(query);

        int user_id = result.value(0).toInt();
        QString username = result.value(1).toString();
        QString password = result.value(2).toString();
        QString email = result.value(4).toString();

        return User(user_id, username, password, email);

}

void QueryHandler::updateUser(User updated_user)
{
    QSqlQuery query;
    query.prepare("UPDATE Users SET username = :username, email = :email, password = :password WHERE user_id = :userId");

    query.bindValue(":username", updated_user.getUsername());
    query.bindValue(":email", updated_user.getEmail());
    query.bindValue(":password", updated_user.getPassword());
    query.bindValue(":userId", updated_user.getId());

    if (!query.exec()) {
        qDebug() << "Error updating user profile:" << query.lastError().text();
    } else {
        qDebug() << "User profile updated successfully for user ID:" << updated_user.getId();
    }
}

QVector<IChat *> QueryHandler::retrieveChats(int id_user)
{
    QSqlQuery query;
    QVector<IChat*> chats;

    QString sql_query=QString("SELECT c.chat_id, c.chat_type, c.creator_id "
                                "FROM Chats c JOIN ChatUsers cu ON c.chat_id = cu.chat_id "
                                "WHERE cu.user_id = %1").arg(id_user);
    query.prepare(sql_query);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError();
        return chats;
    }

    while(query.next())
    {
        int chat_id=query.value(0).toInt();
        QString chat_type=query.value(1).toString();
        IChat* chat;

        if(chat_type=="group")
        {
            chat= new GroupChat(chat_id,query.value(2).toInt());
        }
        else chat=new DirectMessageChat(chat_id);

        QSqlQuery userQuery;

        userQuery.prepare("SELECT Users.user_id FROM Users "
                          "JOIN ChatUsers ON Users.user_id = ChatUsers.user_id "
                          "WHERE ChatUsers.chat_id = :chat_id");
        userQuery.bindValue(":chat_id", chat_id);

        while(userQuery.next())
        {
            chat->addUser(this->retrieveUser(userQuery.value(0).toInt()));
        }

        QSqlQuery messageQuery;
        messageQuery.prepare("SELECT Messages.* FROM Messages WHERE Messages.chat_id = :chat_id");
        messageQuery.bindValue(":chat_id", chat_id);

        while (messageQuery.next()) {

            IMessage* message;
            if(messageQuery.value("continut").isNull())
            {
                message=new FileMessage(messageQuery.value("filename").toString(),messageQuery.value("file_content").toString(),messageQuery.value("sender_id").toInt(),messageQuery.value("chat_id").toInt(),messageQuery.value("message_id").toInt());

            }
            else
            {
                message=new TextMessage(messageQuery.value("content").toString(),messageQuery.value("sender_id").toInt(),messageQuery.value("chat_id").toInt(),messageQuery.value("message_id").toInt());
            }

            chat->addMessage(message);
        }
        chats.append(chat);
    }
    return chats;

}

bool QueryHandler::directMessageChatExists(int user1_id, int user2_id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Chats c "
                  "JOIN ChatUsers cu1 ON c.chat_id = cu1.chat_id "
                  "JOIN ChatUsers cu2 ON c.chat_id = cu2.chat_id "
                  "WHERE c.chat_type = 'direct' AND "
                  "(cu1.user_id = :user1_id AND cu2.user_id = :user2_id) OR "
                  "(cu1.user_id = :user2_id AND cu2.user_id = :user1_id)");
    query.bindValue(":user1_id", user1_id);
    query.bindValue(":user2_id", user2_id);

    if (!query.exec()) {
        qDebug() << "Error checking direct message chat existence:" << query.lastError();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}

int QueryHandler::createDirectMessageChat(int user1_id, int user2_id)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Chats (chat_type,creator_id) VALUES ('direct',:user1_id)");
    query.bindValue(":user1_id",user1_id);
    if (!query.exec()) {
        qDebug() << "Error creating direct message chat:" << query.lastError();
        return -1;
    }

    int chat_id = query.lastInsertId().toInt();

    return chat_id;
}

void QueryHandler::addUserToChat(int chat_id, int user_id)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ChatUsers (chat_id, user_id) VALUES (:chat_id, :user_id)");
    query.bindValue(":chat_id", chat_id);
    query.bindValue(":user_id", user_id);

    if(!query.exec())
    {
        qDebug()<<"Error adding users to chat";
    }
    else qDebug()<<"User with id "<<user_id<<" added";
}

int QueryHandler::getUserId(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT user_id from Users where username= :username");
    query.bindValue(":username",username);

    if(!query.exec())
    {
        qDebug()<<"Error";
    }

    int user_id=query.value(0).toInt();

    return user_id;

}
