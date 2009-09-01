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
void MadNet::run(){
	exec();
}
void MadNet::bytesWrite(qint64 size){
	qDebug() << size;
}
void MadNet::prepareClient() {
	client = server.nextPendingConnection();
	server.close();
	emit connectionStart();
	connect(client,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWrite(qint64)));
	qDebug() << "connected";
}

void MadNet::sendBuffer(QByteArray *buffer) {
		

	int result=client->write(*buffer);
	qDebug() << result;
		//if (result==-1) emit error();
		//  emit sendDone();
		delete buffer;

}
