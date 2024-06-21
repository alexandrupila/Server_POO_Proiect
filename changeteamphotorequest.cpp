#include "changeteamphotorequest.h"

ChangeTeamPhotoRequest::ChangeTeamPhotoRequest() {}

void ChangeTeamPhotoRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int team_id=request["team_id"].toInt();
    QString photo=request["photo"].toString();

    qh.setTeamPhoto(team_id,photo);
}
