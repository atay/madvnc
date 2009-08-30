/*
 * MadServer.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */
#include "MadNet.h"


MadNet::MadNet(QObject * parent){
	server.listen(QHostAddress::Any,7777);
	connect(&server,SIGNAL(newConnection()),this,SLOT(prepareClient()));
	
	
}
void MadNet::prepareClient() {
	client = server.nextPendingConnection();
	server.close();
	emit connectionStart();
}

void MadNet::sendBuffer(QByteArray & buffer) {


		int result=client->write(buffer);

		//if (result==-1) emit error();
		qDebug() << client->bytesToWrite();
		//  emit sendDone();
}
