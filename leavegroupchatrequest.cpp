#include "leavegroupchatrequest.h"

LeaveGroupChatRequest::LeaveGroupChatRequest() {}

void LeaveGroupChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int chat_id=request["chat_id"].toInt();

    qh.leaveGroupChat(user_id,chat_id);

    //response????
}
