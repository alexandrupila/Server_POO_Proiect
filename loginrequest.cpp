#include "loginrequest.h"
#include "user.h"
#include "mytcpserver.h"
#include "queryhandler.h"
#include "datatransferhandler.h"
#include "loginresponse.h"

LoginRequest::LoginRequest() {}

void LoginRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    QString email=request.value("email").toString();
    QString password=request.value("password").toString();

    qDebug()<<"email:"<<email<<"\n";
    qDebug()<<"password:"<<password<<"\n";

    if(!qh.checkCredentials(email,password))
    {
        return;
    }

    IUser* user_nou=qh.retrieveNewUser(email);

    IResponse *resp=new LoginResponse(user_nou);
    resp->sendResponse(clientSocket);

    // DataTransferHandler* transferhandler=new DataTransferHandler(clientSocket);
    // transferhandler->sendDataToClient(user_nou.serialize().toJson());

}
