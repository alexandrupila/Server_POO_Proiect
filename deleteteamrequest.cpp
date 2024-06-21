#include "deleteteamrequest.h"

DeleteTeamRequest::DeleteTeamRequest() {}

void DeleteTeamRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["user_id"].toInt();

    IResponse* resp=nullptr;

    if(qh.isAdmin(user_id,team_id))
    {
        qh.deleteTeam(team_id);
        resp=new OkResponse("sterge team");
    }
    else
    {
        //TODO TRIMITE RASPUNS PRIN CARE SA ZICA CA NU E OK
        resp=new ErrorResponse();
    }

    resp->sendResponse(clientSocket);

}
