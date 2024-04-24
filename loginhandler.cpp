#include "loginhandler.h"

LoginHandler::LoginHandler(QObject *parent)
    : QObject{parent}
{}

void LoginHandler::processLoginRequest(QJsonObject jsonData, QTcpSocket *clientSocket)
{

}
