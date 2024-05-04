#include "okresponse.h"
#include "mytcpserver.h"

OkResponse::OkResponse(QString reason)
{
    this->reason=reason;
}

void OkResponse::sendResponse(QTcpSocket *clientsocket)
{
    QJsonObject jsonResponse;
    jsonResponse["request_type"]="validare";
    jsonResponse["authentification"]="ok";
    jsonResponse["reason"]=this->reason;

    QJsonDocument jsonDoc(jsonResponse);


    //MyTcpServer::getInstance().sendDataToClient(jsonDoc.toJson(),clientsocket->socketDescriptor());
}
