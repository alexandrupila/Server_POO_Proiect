#include "errorresponse.h"
#include "mytcpserver.h"
#include "datatransferhandler.h"
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

    DataTransferHandler* transferHandler=new DataTransferHandler(clientsocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());

}
