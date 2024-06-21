#include "createdirectmessagechatrequest.h"
#include "queryhandler.h"
#include "directmessagechat.h"
#include "errorresponse.h"
#include "okresponse.h"
CreateDirectMessageChatRequest::CreateDirectMessageChatRequest() {}

void CreateDirectMessageChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{

    //VERIFICA CA EXISTA USER UL CELALALT
    //DE TRIMIS NOT OK RESPONSE DACA USER NAME UL CELALALT NU E VALID
    QueryHandler &qh=QueryHandler::getInstance();

    int user1_id=request.value("user_id").toInt();
    QString user2_name=request.value("seconduser_name").toString();
    int user2_id=qh.getUserId(user2_name);

    if(user2_id<1 or user1_id==user2_id)
    {
        IResponse* resp=new ErrorResponse();
        resp->sendResponse(clientSocket);
        return;
    }

    QString chat_name=request.value("chat_name").toString();
    bool chatExists = qh.directMessageChatExists(user1_id, user2_id);
    int chat_id;

    IResponse* response=nullptr;

    if(!chatExists)
    {
        chat_id = qh.createDirectMessageChat(user1_id,chat_name);

        qh.addUserToChat(chat_id, user1_id);
        qh.addUserToChat(chat_id, user2_id);

        DirectMessageChat* dm_chat=dynamic_cast<DirectMessageChat*>(qh.retrieveSpecificChat(chat_id));

        QJsonObject serialized_chat=dm_chat->serialize().object();

        response=new OkResponse(serialized_chat,"create direct_chat");

    }
    else
    {
        response=new ErrorResponse();
    }

    response->sendResponse(clientSocket);

}
