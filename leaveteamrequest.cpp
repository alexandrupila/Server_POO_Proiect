#include "leaveteamrequest.h"

LeaveTeamRequest::LeaveTeamRequest() {}

void LeaveTeamRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    int team_id=request["team_id"].toInt();

    qh.deleteUserFromTeam(team_id,user_id);
}
