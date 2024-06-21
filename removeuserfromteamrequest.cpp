#include "removeuserfromteamrequest.h"

RemoveUserFromTeamRequest::RemoveUserFromTeamRequest() {}

void RemoveUserFromTeamRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_requester_id=request.value("user_id").toInt();
    int user_to_remove_id=request.value("user_to_remove_id").toInt();
    int team_id=request.value("team_id").toInt();

    IResponse* resp=nullptr;

    if(qh.isAdmin(user_requester_id,team_id))
    {
        if(!qh.isAdmin(user_to_remove_id,team_id) and user_requester_id!=user_to_remove_id)
        {
            qh.deleteUserFromTeam(team_id,user_to_remove_id);
            resp=new OkResponse("elimina membru");
        }
        else
        {
            //nu se poate sterge un admin
            resp=new ErrorResponse();
        }
    }
    else
    {
        //raspuns ca user ul nu este admin
        resp=new ErrorResponse();
    }

    resp->sendResponse(clientSocket);
}
