#include "loginresponse.h"
#include "datatransferhandler.h"

LoginResponse::LoginResponse() {}

void LoginResponse::sendResponse(QTcpSocket *clientsocket)
{
    QJsonObject jsonObj=this->requested_user->serialize().object();

    jsonObj["response_type"]="login";
    jsonObj["request_type"]="user";

    QJsonDocument jsonDoc(jsonObj);

    DataTransferHandler* transferHandler=new DataTransferHandler(clientsocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());
}
