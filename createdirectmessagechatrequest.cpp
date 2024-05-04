#include "createdirectmessagechatrequest.h"
#include "queryhandler.h"
#include "directmessagechat.h"
#include "okdirectchatresponse.h"
CreateDirectMessageChatRequest::CreateDirectMessageChatRequest() {}

void CreateDirectMessageChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler &qh=QueryHandler::getInstance();

    int user1_id=request.value("user_id").toInt();
    QString user2_name=request.value("seconduser_name").toString();
    int user2_id=qh.getUserId(user2_name);
    QString chat_name=request.value("chat_name").toString();

    bool chatExists = qh.directMessageChatExists(user1_id, user2_id);
    int chat_id;
    if(!chatExists)
    {
        chat_id = qh.createDirectMessageChat(user1_id,chat_name);

        qh.addUserToChat(chat_id, user1_id);
        qh.addUserToChat(chat_id, user2_id);
    }
    else return;

    DirectMessageChat* dm_chat=new DirectMessageChat(1,"chat_test");

    //User user1=qh.retrieveUser(user1_id);
    //User user2=qh.retrieveUser(user2_id);

    User user1(10,"u1","m1","p1");
    User user2(11,"u2","m2","p2");

    dm_chat->addUser(user1);
    dm_chat->addUser(user2);

    IResponse* response=new OkDirectChatResponse(dm_chat);

    response->sendResponse(clientSocket);

}
