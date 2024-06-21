#include "createteamrequest.h"

CreateTeamRequest::CreateTeamRequest() {}

void CreateTeamRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int creator_id=request["creator_id"].toInt();
    QString team_name=request["group_name"].toString();

    int team_id=qh.createTeam(creator_id,team_name);

    //TO DO: de returnat team ul si de terminat functia din query handler de returnat un team

    ITeam* created_team=qh.retrieveTeam(team_id);

    QJsonObject jsonObj=created_team->serialize().object();

    IResponse * resp=new OkResponse(jsonObj,"create team");

    resp->sendResponse(clientSocket);
}
