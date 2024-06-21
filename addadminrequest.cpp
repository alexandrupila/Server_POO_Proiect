#include "addadminrequest.h"

AddAdminRequest::AddAdminRequest() {}

void AddAdminRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    QString username_to_add=request["username"].toString();
    int user_id=qh.getUserId(username_to_add);
    int team_id=request["team_id"].toInt();
    int request_sender_id=request["user_id"].toInt();

    IResponse* resp=nullptr;

    if(user_id==-1 or qh.isAdmin(user_id,team_id) or !qh.isAdmin(request_sender_id,team_id))
    {
        resp=new ErrorResponse();
    }
    else
    {
        qh.makeUserAdmin(team_id,user_id);
        resp=new OkResponse("adauga membru_in_team");
    }

    resp->sendResponse(clientSocket);
}
