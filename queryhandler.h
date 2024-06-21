#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include <QObject>
#include <QtSql>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include "IMessage.h"
#include "user.h"
#include "ichat.h"
#include "ichannel.h"
#include "team.h"
#include "assignment.h"
#include "submission.h"

class QueryHandler
{
private:
    QMutex m_mutex;
    QSqlDatabase db;
    static QueryHandler* instance;
    QString connectionName;
    int connection_nr;
    QueryHandler();
    ~QueryHandler() {}
public:
    void setConnNr(int nr) {this->connection_nr=nr;}
    void connectDB();
    void disconnectDB();

    static QueryHandler& getInstance();
    static void destroyInstance();
    QVariantList queryDB(QSqlQuery query);
    IUser* retrieveNewUser(QString email);
    void insertUser(IUser* new_user);
    bool userExists(const QString& email, const QString& username, const QString& password);
    bool checkCredentials(const QString& email,const QString& password);
    IUser* retrieveUser(int id_user);
    void updateUser(IUser* updated_user);
    void setUserPhoto(int user_id,QString base64photo);
    void setTeamPhoto(int team_id,QString base64photo);

    QVector<IUser*> retrieveUsersInChat(int chat_id);
    QVector<IMessage*> retrieveMessagesInChat(int chat_id);
    IChat* retrieveSpecificChat(int chat_id);
    IMessage* retrieveSpecificMessage(int message_id);
    QVector<IChat*> retrieveChats(int id_user);

    bool directMessageChatExists(int user1_id,int user2_id);
    bool chatExists(int chat_id);
    int createDirectMessageChat(int creator_id,QString chat_name);
    int createGroupChat(int creator_id,QString chat_name);
    void addUserToChat(int chat_id,int user_id);
    void removeUserFromChat(int chat_id,int user_id);
    int getUserId(QString username);
    void updateUserChats(QString new_username);

    QVector<IChannel*> retrieveChannels(int team_id);
    QVector<IChannel*> retrievePublicChannels(int team_id);
    QVector<IUser*> retrieveUsersInTeam(int team_id);
    QVector<IUser*> retrieveAdminsInTeam(int team_id);
    QVector<IAssignment*> retrieveAssignments(int team_id);
    QVector<IAssignment*> retrieverAdminAssignments(int user_id,int team_id);
    QVector<ISubmission*> retrieveSubmissions(int assignment_id);
    QVector<ITeam*> retrieveTeams(int user_id);
    ITeam* retrieveTeam(int team_id);
    void deleteTeam(int team_id);

    IChannel* retrieveChannel(int channel_id);
    int createChannel(int creator_id,int team_id,QString channel_name,QString type);

    int addMessage(IMessage* new_message);
    int createTeam(int creator_id,QString team_name);
    void addUserToTeam(int team_id,int user_id);
    void deleteUserFromTeam(int team_id,int user_id);
    void removeAdmin(int user_id,int team_id);
    void makeUserAdmin(int team_id,int user_id);
    void deleteChat(int chat_id);
    void leaveGroupChat(int user_id,int chat_id);

    int createAssignment(IAssignment* assign);
    IAssignment* retrieveSpecificAssignment(int assign_id);


    int addSubmission(int user_id,int assignment_id,ISubmission* subm);
    bool hasSubmitted(int user_id,int assignment_id);

    bool isGraded(int submission_id);
    void gradeSubmission(int submission_id, int grade);
    ISubmission* retrieveSpecificSubmission(int submission_id);
    ISubmission* retrieveSubmissionByID(int user_id,int assignment_id);

    bool isCreator(int user_id,int chat_id);
    bool isAdmin(int user_id,int team_id);

    bool isInTeam(int user_id,int team_id);
    bool isInChat(int user_id,int chat_id);
};

#endif // QUERYHANDLER_H
