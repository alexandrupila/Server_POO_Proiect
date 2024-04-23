#include "mainwindow.h"

#include <QApplication>
#include "mytcpserver.h"
#include "queryhandler.h"
#include "logger.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();


    //MyTcpServer server;
    if (!MyTcpServer::getInstance().listen(QHostAddress::Any, 12345)) {
        qDebug() << "Failed to start server:" << MyTcpServer::getInstance().errorString();
        return 1;
    } else {
        Logger::logGeneral("Server started on port 12345.");
    }

    return a.exec();
}
