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

signals:
	void connectionStart();



private:

	QTcpSocket *client;
	QTcpServer server;

};

#endif /* MADNET_H_ */
