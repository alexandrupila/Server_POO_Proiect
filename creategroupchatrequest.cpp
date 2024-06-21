#include "creategroupchatrequest.h"
#include "queryhandler.h"

CreateGroupChatRequest::CreateGroupChatRequest() {}

void CreateGroupChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request.value("creator_id").toInt();
    QString chat_name=request.value("chat_name").toString();

    int chat_id=qh.createGroupChat(user_id,chat_name);
    qh.addUserToChat(chat_id,user_id);

    QJsonObject serialized_chat=qh.retrieveSpecificChat(chat_id)->serialize().object();

    //FIX TEMPORAR
    serialized_chat.remove("request_type");

    IResponse* resp=new OkResponse(serialized_chat,"create group_chat");
    resp->sendResponse(clientSocket);

}
