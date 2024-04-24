#include "errorresponse.h"
#include "mytcpserver.h"
ErrorResponse::ErrorResponse(QString reason)
{
    this->reason=reason;
}

void ErrorResponse::sendResponse(QTcpSocket *clientsocket)
{
    QJsonObject jsonResponse;

    jsonResponse["response_type"]="error";
    jsonResponse["reason"]=this->reason;

    QJsonDocument jsonDoc(jsonResponse);

    MyTcpServer::getInstance().sendDataToClient(jsonDoc.toJson(),clientsocket->socketDescriptor());
}
