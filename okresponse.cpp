#include "okresponse.h"
#include "mytcpserver.h"
#include "datatransferhandler.h"

OkResponse::OkResponse(QString reason)
{
    this->reason=reason;

    this->response["request_type"]="validare";
    this->response["result"]="ok";
    this->response["validation_type"]=this->reason;
}

OkResponse::OkResponse(QJsonObject object, QString reason)
{
    this->response=object;

    this->reason=reason;
    this->response["request_type"]="validare";
    this->response["result"]="ok";
    this->response["validation_type"]=this->reason;

}

void OkResponse::sendResponse(QTcpSocket *clientsocket)
{

    QJsonDocument jsonDoc(response);

    DataTransferHandler* transferhandler=new DataTransferHandler(clientsocket);
    transferhandler->sendDataToClient(jsonDoc.toJson());
}
