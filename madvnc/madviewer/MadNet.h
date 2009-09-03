#ifndef MADNET_H
#define MADNET_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>

class QThread;
class MadNet: public QThread{
Q_OBJECT

public:
        MadNet(QObject *parent = 0);

protected:
        void run();

public slots:
        void prepareClient();
        void sendCommands(QByteArray*);
        void bytesWrite(qint64);

signals:
        void connectionStart();



private:

        QTcpSocket *client;
        QTcpServer server;

};

#endif // MADNET_H
