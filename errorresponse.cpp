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

    jsonResponse["request_type"]="validare";
    jsonResponse["result"]="not ok";

    QJsonDocument jsonDoc(jsonResponse);

    DataTransferHandler* transferHandler=new DataTransferHandler(clientsocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());

}
