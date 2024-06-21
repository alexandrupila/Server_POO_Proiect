#include "leavedirectchatrequest.h"

LeaveDirectChatRequest::LeaveDirectChatRequest() {}

void LeaveDirectChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int chat_id=request["chat_id"].toInt();

    qh.deleteChat(chat_id);

    //eventual response daca e nevoie, desi nu prea cred

    IResponse* resp=new OkResponse("paraseste direct_chat");
    resp->sendResponse(clientSocket);
}
