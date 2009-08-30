/*
 * MadServer.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADNET_H_
#define MADNET_H_

#include <QTcpServer>
#include <QTcpSocket>


class MadNet: public QObject{
Q_OBJECT

public:
	MadNet(QObject *parent = 0);

public slots:
	void prepareClient();
	void sendBuffer(QByteArray&);


signals:
	void connectionStart();


private:

	QTcpSocket *client;
	QTcpServer server;

};

#endif /* MADNET_H_ */
