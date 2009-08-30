/*
 * MadServer.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */
#include "MadServer.h"

MadServer::MadServer(QObject * parent){
	listen(QHostAddress::LocalHost,7777);
	qDebug("MadServer start listening");
	connect(this,SIGNAL(newConnection()),this,SLOT(prepareClient()));
}
void MadServer::prepareClient() {
	client = nextPendingConnection();
	close();
	emit connectionStart();
	qDebug("connectionStart() emited");
}

void MadServer::sendWindow(QPixmap qpix ) {


		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_1);

		out << quint16(0);
		out << qpix;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		client->write(block);
		qDebug("window send");
}
