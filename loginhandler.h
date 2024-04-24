#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include <QObject>
#include <QJsonObject>
#include "QTcpSocket"

class LoginHandler : public QObject
{
    Q_OBJECT
public:
    explicit LoginHandler(QObject *parent = nullptr);

signals:
public slots:
    void processLoginRequest(QJsonObject jsonData,QTcpSocket* clientSocket);
};

#endif // LOGINHANDLER_H
