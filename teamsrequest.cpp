#include "teamsrequest.h"
#include "team.h"
#include "queryhandler.h"

TeamsRequest::TeamsRequest() {}

void TeamsRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request.value("user_id").toInt();

    QVector<ITeam*> teams=qh.retrieveTeams(user_id);

    QJsonObject obj;
    QJsonArray teamsArray;

    for(ITeam* team_it: teams)
    {
        QJsonObject team_obj=team_it->serialize().object();
        team_obj["is_admin"]=qh.isAdmin(user_id,team_it->getId());
        teamsArray.append(team_obj);
    }

    obj["teams"]=teamsArray;
    obj["request_type"]="teams";

    QJsonDocument doc(obj);

    //TODO: Cu datatransferhandler si cu response

    DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
    transferHandler->sendDataToClient(doc.toJson());


}
