#include "deletegrouprequest.h"

DeleteGroupRequest::DeleteGroupRequest() {}

void DeleteGroupRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int chat_id=request["chat_id"].toInt();
    int user_id=request["user_id"].toInt();

    IResponse* resp=nullptr;

    if(qh.isCreator(user_id,chat_id))
    {
        qh.deleteChat(chat_id);
        resp=new OkResponse("sterge grupul");
    }
    else
    {
        //raspuns sa zica ca nu e ok
        resp=new ErrorResponse();
    }

    resp->sendResponse(clientSocket);
}
