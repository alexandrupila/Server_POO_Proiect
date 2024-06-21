#include "queryhandler.h"
#include "groupchat.h"
#include "directmessagechat.h"
#include "filemessage.h"
#include "textmessage.h"
#include "privatechannel.h"
#include "publicchannel.h"

QueryHandler* QueryHandler::instance=nullptr;

QueryHandler::QueryHandler()
{
    QString serverName = "DESKTOP-JBOB4F7\\SQLEXPRESS";
    QString dbName = "ATMTeams_DB";
    QString dsn = QString("DRIVER={SQL Server};Server=%1;Database=%2;Trusted_Connection=Yes;").arg(serverName).arg(dbName);

    this->connectionName=dsn;
}


void QueryHandler::connectDB()
{
    this->m_mutex.lock();
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(this->connectionName);
    if (db.open()) {
        qDebug() << "Conexiunea la baza de date a fost stabilita cu succes!";
    } else {
        qDebug()<<db.lastError();
        qDebug() << "Eroare la conectarea la baza de date";
    }

}

void QueryHandler::disconnectDB()
{
    QSqlDatabase database=QSqlDatabase::database();
    db.close();
    this->m_mutex.unlock();
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
            //qDebug()<<row;
        }
    }
    else qDebug()<<"Database query failed."<<query.lastError().text();

    return result;

}

IUser* QueryHandler::retrieveNewUser(QString email)
{
    QSqlQuery query;

    query.prepare("select * from Users where email= :email");
    query.bindValue(":email", email);
    QVariantList result = queryDB(query);

        int user_id = result.value(0).toInt();
        QString username = result.value(1).toString();
        QString password = result.value(2).toString();
        QString email_user = result.value(3).toString();
        QString base64photo=result.value(4).toString();
        IUser* u=new User(user_id, username, email_user,password,base64photo);
        return u;
}

void QueryHandler::insertUser(IUser* new_user)
{
    QSqlQuery query;

    query.prepare("insert into Users (username, password, email, photo) values (:username, :password, :email, :photo)");

    query.bindValue(":username", new_user->getUsername());
    query.bindValue(":password", new_user->getPassword());
    query.bindValue(":email", new_user->getEmail());
    query.bindValue(":photo", new_user->getPhoto());


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

    query.prepare("select COUNT(*) from Users where email= :email");
    query.bindValue(":email", email);

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

    query.prepare("select COUNT(*) as nr_users from Users where email= :email and password= :password");

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

IUser* QueryHandler::retrieveUser(int id)
{
    QSqlQuery query;

    query.prepare("select * from users where user_id= :user_id");

    query.bindValue(":user_id",id);

    QVariantList result =this->queryDB(query);
    int user_id = result.value(0).toInt();
    QString username = result.value(1).toString();
    QString password = result.value(2).toString();
    QString email_user = result.value(3).toString();
    QString base64photo=result.value(4).toString();

    IUser* u=new User(user_id, username, email_user,password,base64photo);

    return u;

}

void QueryHandler::updateUser(IUser* updated_user)
{
    QSqlQuery query;
    query.prepare("update Users SET username= :username, email = :email, password= :password where user_id = :userId");

    query.bindValue(":username", updated_user->getUsername());
    query.bindValue(":email", updated_user->getEmail());
    query.bindValue(":password", updated_user->getPassword());
    query.bindValue(":userId", updated_user->getId());

    if (!query.exec()) {
        qDebug() << "error updating user profile" << query.lastError().text();
    } else {
        qDebug() << "user profile updated successfully for user id" << updated_user->getId();
    }
}

void QueryHandler::setUserPhoto(int user_id, QString base64photo)
{
    QSqlQuery query;
    query.prepare("update Users set photo = :photo where user_id = :userId");

    query.bindValue(":photo", base64photo);
    query.bindValue(":userId",user_id);

    if (!query.exec()) {
        qDebug() << "error updating user profile" << query.lastError().text();
    } else {
        qDebug() << "user photo set for user ID:" << user_id;
    }
}

void QueryHandler::setTeamPhoto(int team_id, QString base64photo)
{
    QSqlQuery query;
    query.prepare("update Teams set team_photo = :photo where team_id = :team_id");

    query.bindValue(":photo", base64photo);
    query.bindValue(":team_id",team_id);

    if (!query.exec()) {
        qDebug() << "error updating team photo" << query.lastError().text();
    } else {
        qDebug() << "team photo set for team ID:" << team_id;
    }
}

QVector<IUser*> QueryHandler::retrieveUsersInChat(int chat_id)
{
    QVector<IUser*> users;
    QSqlQuery query;
    query.prepare("select Users.user_id, Users.username from Users join ChatUsers on Users.user_id = ChatUsers.user_id where ChatUsers.chat_id = :chat_id");
    query.bindValue(":chat_id", chat_id);

    if (query.exec()) {
        while (query.next()) {
            IUser* u=new User(query.value("user_id").toInt(),query.value("username").toString());
            users.append(u);
        }
    } else {
        qDebug() << "Error retrieving users in chat:" << query.lastError().text();
    }

    return users;
}

QVector<IMessage *> QueryHandler::retrieveMessagesInChat(int chat_id)
{
    QVector<IMessage *> messages;
    QSqlQuery query;
    query.prepare("select message_id, sender_id, content, filename, file_content,time from Messages WHERE chat_id = :chat_id");
    query.bindValue(":chat_id", chat_id);
    if (query.exec()) {
        while (query.next()) {
            IMessage *message = nullptr;
            if (query.value("filename").isNull()) {
                TextMessage *textMessage = new TextMessage(query.value("content").toString(),query.value("sender_id").toInt(),chat_id,query.value("time").toString(),query.value("message_id").toInt());
                message = textMessage;
            } else {
                FileMessage *fileMessage = new FileMessage(query.value("filename").toString(),query.value("file_content").toString(),query.value("sender_id").toInt(),chat_id,query.value("time").toString(),query.value("message_id").toInt());
                message = fileMessage;
            }
            IUser* u=this->retrieveUser(query.value("sender_id").toInt());
            message->setSenderName(u->getUsername());
            messages.append(message);
        }
    } else {
        qDebug() << "Error retrieving messages:" << query.lastError().text();
    }

    return messages;
}

IChat *QueryHandler::retrieveSpecificChat(int chat_id)
{
    QSqlQuery query;
    query.prepare("select chat_id, chat_type, creator_id,chat_name from Chats where chat_id = :chat_id");
    query.bindValue(":chat_id", chat_id);
    if (!query.exec()) {
        qDebug() << "error retrieving chat" << query.lastError().text();
        return nullptr;
    }

    if (query.next()) {
        QString chat_type = query.value("chat_type").toString();

        if (chat_type == "direct") {
            DirectMessageChat *chat = new DirectMessageChat(query.value("chat_id").toInt(),query.value("chat_name").toString());
            chat->setUserList(retrieveUsersInChat(chat_id));
            chat->setMessageList(retrieveMessagesInChat(chat_id));
            return chat;
        } else if (chat_type == "group") {
            GroupChat *chat = new GroupChat(query.value("chat_id").toInt(),query.value("creator_id").toInt(),query.value("chat_name").toString());
            chat->setUserList(retrieveUsersInChat(chat_id));
            chat->setMessageList(retrieveMessagesInChat(chat_id));
            return chat;
        }
    }
    else {
        qDebug() << "no chat found with chat_id" << chat_id;
        return nullptr;
    }
}

IMessage *QueryHandler::retrieveSpecificMessage(int message_id)
{    IMessage *message = nullptr;

    QSqlQuery query;
    query.prepare("SELECT sender_id, chat_id, content, filename, file_content, time FROM Messages WHERE message_id = :message_id");
    query.bindValue(":message_id", message_id);
    if (query.exec()) {
        if(query.next())
        {
        int sender_id = query.value("sender_id").toInt();
        int chat_id = query.value("chat_id").toInt();
        QString content = query.value("content").toString();
        QString filename = query.value("filename").toString();
        QByteArray file_content = query.value("file_content").toByteArray();
        QString time=query.value("time").toString();

        IUser* u=this->retrieveUser(query.value("sender_id").toInt());

        if (filename.isEmpty()) {
            message=new TextMessage(content,sender_id,chat_id,time,message_id);
        } else {
            message= new FileMessage(filename,file_content,sender_id,chat_id,time,message_id);
        }
        message->setSenderName(u->getUsername());
        }
    }
    else
    {
        qDebug()<<"message not found with id "<<message_id;
    }
    return message;
}

QVector<IChat *> QueryHandler::retrieveChats(int id_user)
{
    QSqlQuery query;
    QVector<IChat*> chats;

    QString sql_query=QString("select c.chat_id, c.chat_type, c.creator_id,c.chat_name from Chats c join ChatUsers cu on c.chat_id = cu.chat_id where cu.user_id = %1").arg(id_user);
    query.prepare(sql_query);

    if (!query.exec()) {
        qDebug() << "error retrieving chats" << query.lastError();
        return chats;
    }

    while(query.next())
    {
        int chat_id=query.value(0).toInt();
        QString chat_type=query.value(1).toString();
        int creator_id=query.value(2).toInt();
        QString chat_name=query.value(3).toString();
        IChat* chat;

        if(chat_type=="group")
        {
            chat= new GroupChat(chat_id,creator_id,chat_name);
        }
        else chat=new DirectMessageChat(chat_id,chat_name);

        QSqlQuery userQuery;

        userQuery.prepare("select Users.user_id from Users "
                          "join ChatUsers on Users.user_id = ChatUsers.user_id "
                          "where ChatUsers.chat_id = :chat_id");
        userQuery.bindValue(":chat_id", chat_id);

        while(userQuery.next())
        {
            chat->addUser(this->retrieveUser(userQuery.value(0).toInt()));
        }

        QSqlQuery messageQuery;
        messageQuery.prepare("select Messages.* from Messages where Messages.chat_id = :chat_id");
        messageQuery.bindValue(":chat_id", chat_id);

        while (messageQuery.next()) {
            IMessage* message;
            if(messageQuery.value("continut").isNull())
            {
                QString filename=messageQuery.value("filename").toString();
                QString file_content=messageQuery.value("file_content").toString();
                QString time=messageQuery.value("time").toString();
                message=new FileMessage(filename,file_content,messageQuery.value("sender_id").toInt(),messageQuery.value("chat_id").toInt(),time,messageQuery.value("message_id").toInt());
            }
            else
            {
                QString time=messageQuery.value("time").toString();
                message=new TextMessage(messageQuery.value("content").toString(),messageQuery.value("sender_id").toInt(),messageQuery.value("chat_id").toInt(),time,messageQuery.value("message_id").toInt());
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
    query.prepare("select COUNT(*) from Chats c "
                  "join ChatUsers cu1 on c.chat_id = cu1.chat_id "
                  "join ChatUsers cu2 on c.chat_id = cu2.chat_id "
                  "where c.chat_type = 'direct' and "
                  "(cu1.user_id = :user1_id and cu2.user_id = :user2_id) or "
                  "(cu1.user_id = :user2_id and cu2.user_id = :user1_id)");
    query.bindValue(":user1_id", user1_id);
    query.bindValue(":user2_id", user2_id);

    if (!query.exec()) {
        qDebug() << "error checking if dm chat exists" << query.lastError();
        return false;
    }
    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}

bool QueryHandler::chatExists(int chat_id)
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from Chats where chat_id= :chat_id");
    query.bindValue(":chat_id", chat_id);

    if (!query.exec()) {
        qDebug() << "query error" << query.lastError();
        return false;
    }
    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}

int QueryHandler::createDirectMessageChat(int creator_id,QString chat_name)
{
    QSqlQuery query;
    query.prepare("insert into Chats (chat_type,creator_id,chat_name) values ('direct',:user1_id,:chat_name)");
    query.bindValue(":user1_id",creator_id);
    query.bindValue(":chat_name",chat_name);
    if (!query.exec()) {
        qDebug() << "error creating dm chat" << query.lastError();
        return -1;
    }

    int chat_id = query.lastInsertId().toInt();

    return chat_id;
}

int QueryHandler::createGroupChat(int creator_id, QString chat_name)
{
    QSqlQuery query;
    query.prepare("insert into Chats (chat_type,creator_id,chat_name) values ('group',:user1_id,:chat_name)");
    query.bindValue(":user1_id",creator_id);
    query.bindValue(":chat_name",chat_name);
    if (!query.exec()) {
        qDebug() << "error creating group chat" << query.lastError();
        return -1;
    }

    int chat_id = query.lastInsertId().toInt();

    return chat_id;
}

void QueryHandler::addUserToChat(int chat_id, int user_id)
{
    QSqlQuery query;
    query.prepare("insert into ChatUsers (chat_id, user_id) values (:chat_id, :user_id)");
    query.bindValue(":chat_id", chat_id);
    query.bindValue(":user_id", user_id);
    if(!query.exec())
    {
        qDebug()<<"error adding user to chat";
    }
    else qDebug()<<"User with id "<<user_id<<" added";
}

void QueryHandler::removeUserFromChat(int chat_id, int user_id)
{
    QSqlQuery query;
    query.prepare("delete from ChatUsers where chat_id = :chat_id and user_id = :user_id");
    query.bindValue(":chat_id", chat_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "error executing query" << query.lastError().text();
        return;
    }
    qDebug() << "user " << user_id << "removed from chat" << chat_id << "successfully.";
}

int QueryHandler::getUserId(QString username)
{
    QSqlQuery query;
    query.prepare("select user_id from Users where username= :username");
    query.bindValue(":username",username);

    if(!query.exec())
    {
        qDebug()<<"error executing query";
        return -1;
    }
    query.next();
    int user_id=query.value(0).toInt();
    return user_id;

}

QVector<IChannel *> QueryHandler::retrieveChannels(int team_id)
{
    QVector<IChannel *> channels;

    QSqlQuery query;
    query.prepare("select channel_id, name, description, is_private, chat_id from Channels where team_id = :team_id");
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        while (query.next()) {
            int channelId = query.value(0).toInt();
            QString channelName = query.value(1).toString();
            QString description = query.value(2).toString();
            bool isPrivate = query.value(3).toBool();
            int chatId = query.value(4).toInt();

            IChat *chat = retrieveSpecificChat(chatId);
            if (!chat) {
                qDebug() << "Failed to retrieve chat for channel ID" << channelId;
            }

            IChannel *channel = nullptr;
            if (isPrivate) {
                channel = new PrivateChannel(channelName,chatId,channelId);
            } else {
                channel = new PublicChannel(channelName,chatId,channelId);

            }
            GroupChat* gchat=dynamic_cast<GroupChat*>(chat);
            channel->setChannelChat(gchat);
            channels.append(channel);
        }
        qDebug() << "channel retrieved successfully for team id" << team_id;
    } else {
        qDebug() << "failed to retrieve channels for team id" << team_id << ":" << query.lastError().text();
    }

    return channels;
}

QVector<IChannel *> QueryHandler::retrievePublicChannels(int team_id)
{

    QVector<IChannel *> channels;

    QSqlQuery query;
    query.prepare("select channel_id, name, description, is_private, chat_id from Channels where team_id = :team_id");
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        while (query.next()) {
            int channelId = query.value(0).toInt();
            QString channelName = query.value(1).toString();
            QString description = query.value(2).toString();
            bool isPrivate = query.value(3).toBool();
            int chatId = query.value(4).toInt();

            IChat *chat = retrieveSpecificChat(chatId);
            if (!chat) {
                qDebug() << "Failed to retrieve chat for channel ID" << channelId;
            }

            IChannel *channel = nullptr;
            if (isPrivate) {
                channel = new PrivateChannel(channelName,chatId,channelId);
            } else {
                channel = new PublicChannel(channelName,chatId,channelId);
                GroupChat* gchat=dynamic_cast<GroupChat*>(chat);
                channel->setChannelChat(gchat);
                channels.append(channel);

            }

        }
        qDebug() << "channel retrieved successfully for team id" << team_id;
    } else {
        qDebug() << "failed to retrieve channels for team id" << team_id << ":" << query.lastError().text();
    }

    return channels;
}

QVector<IUser*> QueryHandler::retrieveUsersInTeam(int team_id)
{
    QVector<IUser*> users;

    QSqlQuery query;
    query.prepare("select user_id, username from Users where user_id in (select user_id from TeamMembers where team_id = :team_id)");
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        while (query.next()) {
            IUser* u=new User();
            u->setId(query.value(0).toInt());
            u->setUsername(query.value(1).toString());
            users.append(u);
        }
        qDebug() << "users retrieved successfully for team ID" << team_id;
    } else {
        qDebug() << "failed to retrieve users for team ID" << team_id << ":" << query.lastError().text();
    }

    return users;
}

QVector<IUser*> QueryHandler::retrieveAdminsInTeam(int team_id)
{
    QVector<IUser*> admins;

    QSqlQuery query;
    query.prepare("select user_id, username from Users where user_id in (select user_id from TeamAdmins where team_id = :team_id)");
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        while (query.next()) {
            IUser* u=new Admin();
            u->setId(query.value(0).toInt());
            u->setUsername(query.value(1).toString());
            admins.append(u);
        }
        qDebug() << "admins retrieved successfully for team ID" << team_id;
    } else {
        qDebug() << "failed to retrieve admins for team ID" << team_id << ":" << query.lastError().text();
    }

    return admins;
}

QVector<IAssignment*> QueryHandler::retrieveAssignments(int team_id)
{
    QVector<IAssignment*> assignments;

    QSqlQuery query;
    query.prepare("select assignment_id, creator_id, assignment_name, description, due_date from Assignments where team_id = :team_id");
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        while (query.next()) {
            IAssignment* assignment=new Assignment();
            assignment->setId(query.value(0).toInt());
            assignment->setCreatorId(query.value(1).toInt());
            assignment->setAssignmentName(query.value(2).toString());
            assignment->setDescription(query.value(3).toString());
            assignment->setDueDate(query.value(4).toDate());

            QVector<ISubmission*> submissions = retrieveSubmissions(assignment->getId());
            for (const auto& submission : submissions) {
                assignment->addSubmission(submission);
            }

            assignments.append(assignment);
        }
        qDebug() << "assignments retrieved successfully for team ID" << team_id;
    } else {
        qDebug() << "failed to retrieve assignments for team ID" << team_id << ":" << query.lastError().text();
    }

    return assignments;
}

QVector<IAssignment *> QueryHandler::retrieverAdminAssignments(int user_id, int team_id)
{
    QVector<IAssignment*> assignments;

    QSqlQuery query;
    query.prepare("select assignment_id, assignment_name, description, due_date from Assignments where team_id = :team_id and creator_id= :creator_id ");
    query.bindValue(":team_id", team_id);
    query.bindValue(":creator_id",user_id);

    if (query.exec()) {
        while (query.next()) {
            IAssignment* assignment=new Assignment();
            assignment->setCreatorId(user_id);
            assignment->setId(query.value(0).toInt());
            assignment->setAssignmentName(query.value(1).toString());
            assignment->setDescription(query.value(2).toString());
            assignment->setDueDate(query.value(3).toDate());

            QVector<ISubmission*> submissions = retrieveSubmissions(assignment->getId());
            for (const auto& submission : submissions) {
                assignment->addSubmission(submission);
            }

            assignments.append(assignment);
        }
        qDebug() << "assignments retrieved successfully for team ID" << team_id;
    } else {
        qDebug() << "failed to retrieve assignments for team ID" << team_id << ":" << query.lastError().text();
    }

    return assignments;
}

QVector<ISubmission*> QueryHandler::retrieveSubmissions(int assignment_id)
{
    QVector<ISubmission*> submissions;

    QSqlQuery query;
    query.prepare("select submission_id, user_id, filename, file_content, grade from Submissions where assignment_id = :assignment_id");
    query.bindValue(":assignment_id", assignment_id);

    if (query.exec()) {
        while (query.next()) {
            ISubmission* submission=new Submission();
            submission->setId(query.value(0).toInt());
            submission->setUserId(query.value(1).toInt());
            submission->setFilename(query.value(2).toString());
            submission->setFilecontent(query.value(3).toString());
            submission->setGrade(query.value(4).toInt());
            IUser* u=retrieveUser(query.value(1).toInt());

            submission->setUsername(u->getUsername());
            submissions.append(submission);


        }
        qDebug() << "submissions retrieved successfully for assignment" << assignment_id;
    } else {
        qDebug() << "failed to retrieve submissions " << assignment_id << ":" << query.lastError().text();
    }

    return submissions;
}

QVector<ITeam*> QueryHandler::retrieveTeams(int user_id)
{
    QVector<ITeam*> teams;

    QSqlQuery query;
    query.prepare("select team_id, leader_id, team_name, team_photo from Teams where team_id in (select team_id from TeamMembers where user_id = :user_id)");
    query.bindValue(":user_id", user_id);

    if (query.exec()) {
        while (query.next()) {
            ITeam* team =new Team();
            team->setId(query.value(0).toInt());
            team->setCreator_id(query.value(1).toInt());
            team->setTeamName(query.value(2).toString());
            team->setTeamPhoto(query.value(3).toString());

            QVector<IChannel*> channels = retrieveChannels(team->getId());

            QVector<IAssignment*> assignments = retrieveAssignments(team->getId());

            QVector<IUser*> users = retrieveUsersInTeam(team->getId());

            QVector<IUser*> admins = retrieveAdminsInTeam(team->getId());

            team->setChannelList(channels);
            team->setAssignmentList(assignments);
            team->setUserList(users);
            team->setAdminList(admins);

            teams.append(team);
        }
        qDebug() << "teams retrieved successfully for user ID" << user_id;
    } else {
        qDebug() << "failed to retrieve teams for user ID" << user_id << ":" << query.lastError().text();
    }

    return teams;
}

ITeam* QueryHandler::retrieveTeam(int team_id)
{
    ITeam* team=nullptr;
    QSqlQuery query;

    query.prepare("select team_id, leader_id, team_name, team_photo from Teams where team_id = :team_id");
    query.bindValue(":team_id", team_id);
    if (query.exec()) {
        if (query.next()) {
            team=new Team;
            team->setId(query.value(0).toInt());
            team->setCreator_id(query.value(1).toInt());
            team->setTeamName(query.value(2).toString());
            team->setTeamPhoto(query.value(3).toString());
        } else {
            qDebug() << "No team found with ID" << team_id;
            return team;
        }
    } else {
        qDebug() << "Query error " << query.lastError().text();
        return team;
    }

    team->setChannelList(retrieveChannels(team_id));

    team->setAssignmentList(retrieveAssignments(team_id));

    team->setUserList(retrieveUsersInTeam(team_id));

    team->setAdminList(retrieveAdminsInTeam(team_id));

    return team;
}

void QueryHandler::deleteTeam(int team_id)
{
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    try {
        QSqlQuery query;

        query.prepare("delete from Assignments where team_id = :team_id");
        query.bindValue(":team_id", team_id);
        if (!query.exec()) throw std::runtime_error("Failed to delete assignments");

        query.prepare("delete from Channels where team_id = :team_id");
        query.bindValue(":team_id", team_id);
        if (!query.exec()) throw std::runtime_error("Failed to delete channels");

        query.prepare("delete from TeamUsers where team_id = :team_id");
        query.bindValue(":team_id", team_id);
        if (!query.exec()) throw std::runtime_error("Failed to delete team users");

        query.prepare("delete from Teams where team_id = :team_id");
        query.bindValue(":team_id", team_id);
        if (!query.exec()) throw std::runtime_error("Failed to delete team");

        db.commit();
    } catch (const std::exception& e) {
        db.rollback();
        qDebug() << "Transaction failed: " << e.what();
    }
}

IChannel *QueryHandler::retrieveChannel(int channel_id)
{
    QSqlQuery query;
    query.prepare("select channel_id, name, is_private, chat_id from Channels where channel_id = :channel_id");
    query.bindValue(":channel_id", channel_id);
    if (!query.exec()) {
        qDebug() << "Failed to retrieve channel: " << query.lastError().text();
        return nullptr;
    }

    if (query.next()) {
        int cid = query.value(0).toInt();
        QString name = query.value(1).toString();
        bool isPrivate = query.value(2).toBool();
        int chatId = query.value(3).toInt();
        IChat* chat = retrieveSpecificChat(chatId);
        IChannel *channel;
        if (isPrivate) {
            channel = new PrivateChannel(name,chatId,cid);
        } else {
            channel = new PublicChannel(name,chatId,cid);
        }

        GroupChat* gchat=dynamic_cast<GroupChat*>(chat);

        channel->setChannelChat(gchat);

        return channel;
    } else {
        qDebug() << "No channel found with ID: " << channel_id;
        return nullptr;
    }
}

int QueryHandler::createChannel(int creator_id,int team_id, QString channel_name, QString type)
{
    bool isPrivate=0;
    if(type=="private_channel") isPrivate=1;
    int specific_chat_id=this->createGroupChat(creator_id,channel_name+"_chat");

    QSqlQuery query;
    query.prepare("insert into Channels (name, is_private, team_id, chat_id) values (:name, :is_private, :team_id , :chat_id)");
    query.bindValue(":name", channel_name);
    query.bindValue(":is_private", isPrivate);
    query.bindValue(":team_id", team_id);
    query.bindValue(":chat_id", specific_chat_id);

    if (!query.exec()) {
        qDebug() << "Failed to create channel: " << query.lastError().text();
        return -1;
    }
    qDebug() << "Channel created successfully.";

    int channel_id=query.lastInsertId().toInt();

    return channel_id;

}

int QueryHandler::addMessage(IMessage *new_message)
{
    QSqlQuery query;

    if(TextMessage* mesaj_text=dynamic_cast<TextMessage*>(new_message))
    {
        query.prepare("insert into Messages (chat_id, sender_id, content, time) "
                      "values (:chat_id, :sender_id, :content, :time)");
        query.bindValue(":chat_id", mesaj_text->getChatId());
        query.bindValue(":sender_id", mesaj_text->getSenderId());
        query.bindValue(":content", mesaj_text->getContent());
        query.bindValue(":time", mesaj_text->getDate());
    }
    else
    {
        FileMessage* mesaj_fisier=dynamic_cast<FileMessage*>(new_message);
        query.prepare("insert into Messages (chat_id, sender_id, filename, file_content, time) "
                      "values (:chat_id, :sender_id, :filename, :file_content, :time)");
        query.bindValue(":chat_id", mesaj_fisier->getChatId());
        query.bindValue(":sender_id", mesaj_fisier->getSenderId());
        query.bindValue(":filename", mesaj_fisier->getFilename());
        query.bindValue(":file_content", mesaj_fisier->getFileContent());
        query.bindValue(":time", mesaj_fisier->getDate());
    }

    if (query.exec()) {
        qDebug() << "Message added successfully.";
    } else {
        qDebug() << "Error adding message:" << query.lastError().text();
    }

    int message_id=query.lastInsertId().toInt();

    return message_id;

}

int QueryHandler::createTeam(int creator_id, QString team_name)
{
    QSqlQuery query;
    query.prepare("insert into Teams (leader_id, team_name) values (:creator_id, :team_name)");
    query.bindValue(":creator_id", creator_id);
    query.bindValue(":team_name", team_name);

    if (!query.exec()) {
        qDebug() << "Error inserting into the Teams table:" << query.lastError().text();
        return -1;
    }

    int team_id;
    team_id=query.lastInsertId().toInt();
    addUserToTeam(team_id,creator_id);
    makeUserAdmin(team_id,creator_id);

    return team_id;

}

void QueryHandler::addUserToTeam(int team_id, int user_id)
{
    QSqlQuery query;
    query.prepare("insert into TeamMembers (team_id, user_id) values (:team_id, :user_id)");
    query.bindValue(":team_id", team_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error adding user to team:" << query.lastError().text();
    } else {
        qDebug() << "User added to team successfully.";
    }
}

void QueryHandler::deleteUserFromTeam(int team_id, int user_id)
{
    if(isAdmin(user_id,team_id))
    {
        removeAdmin(user_id,team_id);
    }

    QSqlQuery query;
    query.prepare("delete from TeamMembers where team_id = :team_id AND user_id = :user_id");
    query.bindValue(":team_id", team_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }

    qDebug() << "User" << user_id << "removed from team" << team_id << "successfully.";
}

void QueryHandler::removeAdmin(int user_id, int team_id)
{
    QSqlQuery query;
    query.prepare("delete from TeamAdmins where team_id = :team_id and user_id = :user_id");
    query.bindValue(":team_id", team_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }

    qDebug() << "User" << user_id << "removed as admin from team" << team_id << "successfully.";
}

void QueryHandler::makeUserAdmin(int team_id, int user_id)
{
    QSqlQuery query;
    query.prepare("insert into TeamAdmins (team_id, user_id) values (:team_id, :user_id)");
    query.bindValue(":team_id", team_id);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug() << "Error making user admin:" << query.lastError().text();
    } else {
        qDebug() << "User set as admin successfully.";
    }
}

void QueryHandler::deleteChat(int chat_id)
{
    db.transaction();

    QSqlQuery query;
    query.prepare("delete from Messages where chat_id = :chat_id");
    query.bindValue(":chat_id", chat_id);
    if (!query.exec()) {
        qDebug() << "Error deleting messages for chat:" << query.lastError().text();
        db.rollback();
        return;
    }

    query.prepare("delete from ChatUsers where chat_id = :chat_id");
    query.bindValue(":chat_id", chat_id);
    if (!query.exec()) {
        qDebug() << "Error deleting ChatUsers entries for chat:" << query.lastError().text();
        db.rollback();
        return;
    }

    query.prepare("delete from Chats where chat_id = :chat_id");
    query.bindValue(":chat_id", chat_id);
    if (!query.exec()) {
        qDebug() << "Error deleting chat:" << query.lastError().text();
        db.rollback();
        return;
    }
    db.commit();
    qDebug() << "Direct message chat deleted successfully.";
}

void QueryHandler::leaveGroupChat(int user_id, int chat_id)
{
    db.transaction();

    QSqlQuery query;
    query.prepare("delete from ChatUsers where user_id = :user_id AND chat_id = :chat_id");
    query.bindValue(":user_id", user_id);
    query.bindValue(":chat_id", chat_id);
    if (!query.exec()) {
        qDebug() << "Error leaving group chat:" << query.lastError().text();
        db.rollback();
        return;
    }

    db.commit();
    qDebug() << "User left group chat successfully.";
}

int QueryHandler::createAssignment(IAssignment* assign)
{
    QSqlQuery query;
    query.prepare("insert into Assignments (assignment_name, creator_id, due_date, description, team_id) VALUES (:assignment_name , :creator_id , :due_date , :description , :team_id)");

    query.bindValue(":assignment_name", assign->getAssignmentName());
    query.bindValue(":team_id", assign->getTeamId());
    QString dateString=assign->getDate().toString("yyyy-MM-dd");
    query.bindValue(":due_date",dateString);
    query.bindValue(":description",assign->getDescription());
    query.bindValue(":creator_id",assign->getCreatorId());

    if (!query.exec()) {
        qDebug() << "Error inserting into the Assignments table:" << query.lastError().text();
        return -1;
    }

    int assignment_id;

    assignment_id=query.lastInsertId().toInt();

    return assignment_id;
}

IAssignment* QueryHandler::retrieveSpecificAssignment(int assign_id)
{
    IAssignment* assignment=new Assignment();

    QSqlQuery query;
    query.prepare("select team_id, creator_id, assignment_name, description, due_date from Assignments where assignment_id = :assign_id");
    query.bindValue(":assign_id", assign_id);

    if (query.exec()) {
        query.next();
        assignment->setId(assign_id);
        assignment->setTeamId(query.value(0).toInt());
        assignment->setCreatorId(query.value(1).toInt());
        assignment->setAssignmentName(query.value(2).toString());
        assignment->setDescription(query.value(3).toString());
        assignment->setDueDate(query.value(4).toDate());

        QVector<ISubmission*> submissions = retrieveSubmissions(assignment->getId());

            for ( auto& submission : submissions) {
            assignment->addSubmission(submission);


        }
        qDebug() << "Assignment retrieved successfully for assignment ID" << assign_id;
    } else {
        qDebug() << "Failed to retrieve assignments for team ID" << assign_id << ":" << query.lastError().text();
    }

    return assignment;
}

int QueryHandler::addSubmission(int user_id, int assignment_id, ISubmission* subm)
{
    QSqlQuery query;
    query.prepare("insert into Submissions (assignment_id, user_id, filename, file_content, grade) values ( :assign_id, :user_id, :filename, :file_content, :grade)");

    query.bindValue(":assign_id",assignment_id);
    query.bindValue(":user_id",user_id);
    query.bindValue(":filename",subm->getFilename());
    query.bindValue(":file_content",subm->getContent());
    query.bindValue(":grade",-1);

    if(!query.exec())
    {
        qDebug() << "Error inserting into the Assignments table:" << query.lastError().text();
        return -1;
    }

    int subm_id=query.lastInsertId().toInt();

    return subm_id;
}

bool QueryHandler::hasSubmitted(int user_id, int assignment_id)
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from Submissions where user_id = :user_id and assignment_id= :assignment_id");
    query.bindValue(":user_id",user_id);
    query.bindValue(":assignment_id",assignment_id);

    if(query.exec())
    {
        query.next();
        int count = query.value(0).toInt();
        return count > 0;
    }
    else
    {
        qDebug()<<"Error executing query"<<query.lastError().text();
    }

    return false;
}

bool QueryHandler::isGraded(int submission_id)
{
    QSqlQuery query;
    query.prepare("select grade from Submissions where submission_id = :submission_id");
    query.bindValue(":submission_id",submission_id);

    if(query.exec())
    {
        query.next();
        int nota=query.value(0).toInt();
        if(nota!=-1) return 1;
    }
    else
    {
        qDebug()<<"Error executing query"<<query.lastError().text();
    }

    return false;
}

void QueryHandler::gradeSubmission(int submission_id, int grade)
{
    QSqlQuery query;
    query.prepare("update Submissions set grade = :grade where submission_id = :submission_id");
    query.bindValue(":grade",grade);
    query.bindValue(":submission_id",submission_id);

    if(!query.exec())
    {
        qDebug()<<"error executing query"<<query.lastError().text();
    }
}

ISubmission* QueryHandler::retrieveSpecificSubmission(int submission_id)
{
    ISubmission* subm=new Submission();
    QSqlQuery query;
    query.prepare("select assignment_id, user_id, filename, file_content, grade from Submissions where submission_id = :submission_id");
    query.bindValue(":submission_id", submission_id);

    if(query.exec())
    {
        query.next();
        subm->setId(submission_id);
        subm->setAssignId(query.value(0).toInt());
        subm->setUserId(query.value(1).toInt());
        subm->setFilename(query.value(2).toString());
        subm->setFilecontent(query.value(3).toString());
        subm->setGrade(query.value(4).toInt());
        IUser* u=this->retrieveUser(query.value(1).toInt());
        subm->setUsername(u->getUsername());
        return subm;
    }
    else
    {
        qDebug()<<"query failed";
    }

    return subm;
}

ISubmission *QueryHandler::retrieveSubmissionByID(int user_id, int assignment_id)
{
    ISubmission* subm=new Submission();
    QSqlQuery query;
    query.prepare("select assignment_id, user_id, filename, file_content, grade, submission_id from Submissions where user_id = :user_id and assignment_id = :assignment_id");
    query.bindValue(":assignment_id", assignment_id);
    query.bindValue(":user_id",user_id);
    if(query.exec())
    {
        query.next();
        subm->setId(query.value(5).toInt());
        subm->setAssignId(query.value(0).toInt());
        subm->setUserId(query.value(1).toInt());
        subm->setFilename(query.value(2).toString());
        subm->setFilecontent(query.value(3).toString());
        subm->setGrade(query.value(4).toInt());
        IUser* u=this->retrieveUser(query.value(1).toInt());
        subm->setUsername(u->getUsername());
        return subm;
    }
    else
    {
        qDebug()<<"query failed";
    }

    return subm;
}

bool QueryHandler::isCreator(int user_id, int chat_id)
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from Chats where chat_id = :chat_id and creator_id = :user_id");
    query.bindValue(":chat_id",chat_id);
    query.bindValue(":user_id",user_id);

    if (query.exec()) {
        query.next();
            int count = query.value(0).toInt();
            return count > 0;
    }
    else {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
    }

    return false;
}

bool QueryHandler::isAdmin(int user_id, int team_id)
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from TeamAdmins where user_id = :user_id and team_id = :team_id");
    query.bindValue(":user_id", user_id);
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        query.next();
        if (query.value(0).toInt() > 0) return true;
    } else {
        qDebug() << "query error " << query.lastError().text();
    }

    return false;
}

bool QueryHandler::isInTeam(int user_id, int team_id)
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from TeamMembers where user_id = :user_id and team_id= :team_id");

    query.bindValue(":user_id", user_id);
    query.bindValue(":team_id", team_id);

    if (query.exec()) {
        query.next();
        if (query.value(0).toInt() > 0) return true;
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return false;
}

bool QueryHandler::isInChat(int user_id, int chat_id)
{
    QSqlQuery query;
    query.prepare("select COUNT(*) from ChatUsers where user_id = :user_id and chat_id= :chat_id");

    query.bindValue(":user_id", user_id);
    query.bindValue(":chat_id", chat_id);

    if (query.exec()) {
        query.next();
        if (query.value(0).toInt() > 0) return true;
    }
    else
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
        return false;
}
