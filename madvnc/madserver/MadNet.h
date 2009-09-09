/*
 * MadServer.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADNET_H_
#define MADNET_H_


#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>


class MadNet: public QObject{
Q_OBJECT

public:
	MadNet();

protected:
	void run();

public slots:
	void prepareClient();
	void sendBuffer(QByteArray*);
	void bytesWrite(qint64);
	void disconnectClient();
	void stopingWorking();

        void receiveControls();

signals:
	void connectionStart(const QString &);
	void stopWorking();



private:

	QTcpSocket *client;
	QTcpServer server;
	qint16 nextBlock;
    QDataStream controls;

};

#endif /* MADNET_H_ */
