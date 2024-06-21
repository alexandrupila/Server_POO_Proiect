#include "addusertochatrequest.h"

AddUserToChatRequest::AddUserToChatRequest() {}

void AddUserToChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler & qh=QueryHandler::getInstance();

    QString username_to_add=request["username"].toString();
    int user_id=qh.getUserId(username_to_add);
    int chat_id=request["chat_id"].toInt();
    int request_sender_id=request["user_id"].toInt();

    IResponse* resp=nullptr;

    if(user_id==-1 or qh.isInChat(user_id,chat_id) or !qh.isCreator(request_sender_id,chat_id))
    {
        resp=new ErrorResponse();
    }
    else
    {
        qh.addUserToChat(chat_id,user_id);
        resp=new OkResponse("adauga membru");
    }

    resp->sendResponse(clientSocket);
}
