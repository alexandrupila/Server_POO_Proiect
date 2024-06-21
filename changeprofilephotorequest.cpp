#include "changeprofilephotorequest.h"

void ChangeProfilePhotoRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request["user_id"].toInt();
    QString base64photo=request["photo"].toString();

    qh.setUserPhoto(user_id,base64photo);

    //E NEVOIE DE RASPUNS???
}
