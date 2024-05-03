#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QTcpSocket>

class WorkerThread : public QObject
{
    Q_OBJECT
protected:
    qintptr m_socketDescriptor;
    QTcpSocket* clientSocket;
public:
    explicit WorkerThread(QObject *parent = nullptr);
    WorkerThread(qintptr socket_descr) {this->m_socketDescriptor=socket_descr;}
    ~WorkerThread() {}
public slots:
    void process();
    void readClientData();
    void handleDisconnect();
signals:
    void finished();
    void error(QString err);
    void clientConnected(QTcpSocket *clientSocket);
    void clientDisconnected();
};

#endif // WORKERTHREAD_H
