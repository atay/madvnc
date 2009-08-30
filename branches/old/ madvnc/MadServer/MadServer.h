/*
 * MadServer.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADSERVER_H_
#define MADSERVER_H_

#include <QTcpServer>
#include <QTcpSocket>
#include <QPixmap>

class QTcpServer;

class MadServer: public QTcpServer {
Q_OBJECT

public:
	MadServer(QObject *parent = 0);

public slots:
	void prepareClient();
	void sendWindow(QPixmap qpix );


signals:
	void connectionStart();

private:
	QTcpSocket *client;

};

#endif /* MADSERVER_H_ */
