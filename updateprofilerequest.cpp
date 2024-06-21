#include "updateprofilerequest.h"
#include "user.h"
#include "queryhandler.h"
#include "mytcpserver.h"

UpdateProfileRequest::UpdateProfileRequest() {}

void UpdateProfileRequest::processRequest(QJsonObject request, QTcpSocket *clientSocket)
{
    QueryHandler& qh=QueryHandler::getInstance();

    int user_id=request.value("user_id").toInt();

    IUser* user_to_update=qh.retrieveUser(user_id);

    QString username=user_to_update->getUsername();
    QString email=user_to_update->getEmail();
    QString password=user_to_update->getPassword();
    if(!request.value("username").isNull()) username=request.value("username").toString();
    if(!request.value("email").isNull()) email=request.value("email").toString();
    if(!request.value("password").isNull()) password=request.value("password").toString();

    IUser* updated_user=new User(user_id,username,email,password);
    qh.updateUser(updated_user);

    updated_user=qh.retrieveUser(user_id);

    QJsonObject jsonObj =updated_user->serialize().object();
    jsonObj["request_type"]="new_profile";

    QJsonDocument jsonDoc(jsonObj);

    DataTransferHandler* transferHandler=new DataTransferHandler(clientSocket);
    transferHandler->sendDataToClient(jsonDoc.toJson());
}


