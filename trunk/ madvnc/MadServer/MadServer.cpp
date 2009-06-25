/*
 * MadServer.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */
#include <QtCore>
#include <QtGui>
#include "MadServer.h"

MadServer::MadServer(QObject * parent){
	listen(QHostAddress::LocalHost,7777);
}
void MadServer::prepareClient() {
	client = nextPendingConnection();
	close();
	emit connectionStart();
}

void MadServer::sendWindow(QPixmap &qpix ) {


		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_1);

		out << quint16(0);
		out << qpix;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		client->write(block);

}
