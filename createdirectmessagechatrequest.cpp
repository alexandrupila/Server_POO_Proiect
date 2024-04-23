#include "createdirectmessagechatrequest.h"
#include "queryhandler.h"
#include "directmessagechat.h"
#include "mytcpserver.h"
CreateDirectMessageChatRequest::CreateDirectMessageChatRequest() {}

void CreateDirectMessageChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler &qh=QueryHandler::getInstance();


    int user1_id=request.value("user_id").toInt();
    QString user2_name=request.value("seconduser_name").toString();
    int user2_id=qh.getUserId(user2_name);

    bool chatExists = qh.directMessageChatExists(user1_id, user2_id);

    int chat_id;
    if(!chatExists)
    {
        chat_id = qh.createDirectMessageChat(user1_id, user2_id);

        qh.addUserToChat(chat_id, user1_id);
        qh.addUserToChat(chat_id, user2_id);
    }
    else return;

    QString chat_name=QString("%1-%2").arg(user1_id).arg(user2_id);

    DirectMessageChat* dm_chat=new DirectMessageChat(chat_id,chat_name);

    User user1=qh.retrieveUser(user1_id);
    User user2=qh.retrieveUser(user2_id);

    dm_chat->addUser(user1);
    dm_chat->addUser(user2);

    QJsonDocument doc=dm_chat->serialize();

    MyTcpServer::getInstance().sendDataToClient(doc.toJson(),clientSocket->socketDescriptor());
}
