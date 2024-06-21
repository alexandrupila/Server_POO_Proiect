#include "removeuserfromchatrequest.h"

RemoveUserFromChatRequest::RemoveUserFromChatRequest() {}

void RemoveUserFromChatRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_requester_id=request.value("user_id").toInt();
    int user_to_remove_id=request.value("user_to_remove_id").toInt();
    int chat_id=request.value("chat_id").toInt();

    IResponse* resp=nullptr;


    //SA NU LASI PE NIMENI SA ISSI DEA KICK SINGUR!!!!!!!!!


    if(qh.isCreator(user_requester_id,chat_id) and user_requester_id!=user_to_remove_id)
    {
        qh.removeUserFromChat(chat_id,user_to_remove_id);
        resp=new OkResponse("elimina membru");
    }
    else
    {
        resp=new ErrorResponse();
    }

    resp->sendResponse(clientSocket);

}
