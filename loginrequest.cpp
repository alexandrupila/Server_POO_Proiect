#include "loginrequest.h"
#include "user.h"
#include "mytcpserver.h"
#include "queryhandler.h"
#include "datatransferhandler.h"

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
        //return;
    }

    //User user_nou=qh.retrieveNewUser(email);
    User user_nou(0,"abc","def","ghi");

    DataTransferHandler* transferhandler=new DataTransferHandler(clientSocket);
    transferhandler->sendDataToClient(user_nou.serialize().toJson());

   //MyTcpServer::getInstance().sendDataToClient(user_nou.serialize().toJson(),clientSocket->socketDescriptor());

}
