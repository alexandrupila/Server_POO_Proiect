#ifndef DATATRANSFERHANDLER_H
#define DATATRANSFERHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QTcpSocket>
#include <QTimer>


class IRequest;

class DataTransferHandler :public QObject
{
protected:
    QTcpSocket* clientSocket;
    QTimer* timer_repeated_request;
    QJsonObject lastRequest;
    IRequest* repeatedRequest;
public:
    DataTransferHandler();
    DataTransferHandler(QTcpSocket* socket);
    void stopTimer();
    void initRepeatableRequest(IRequest* repeatedRequest,QJsonObject jsonObj);
    ~DataTransferHandler()
    {
        if(this->clientSocket)
        {
            delete this->clientSocket;
        }
        if(this->timer_repeated_request)
        {
            timer_repeated_request->stop();
            delete timer_repeated_request;
        }
        if(this->repeatedRequest)
        {
            delete repeatedRequest;
        }

    }
public slots:
    void readClientData();
    void handleClientDisconnected();
    void sendDataToClients(const QByteArray &data);
    void sendDataToClient(const QByteArray &data);
    void handleClientConnected();
    void repeatRequest();

};

#endif // DATATRANSFERHANDLER_H
