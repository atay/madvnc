/*
 * MadServer.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */
#include "MadNet.h"


MadNet::MadNet(){
	server.listen(QHostAddress::Any,7777);
	connect(&server,SIGNAL(newConnection()),this,SLOT(prepareClient()));
	
	
	
}

void MadNet::bytesWrite(qint64 size){
	
}
void MadNet::prepareClient() {
	client = server.nextPendingConnection();
	server.close();
	emit connectionStart();
	connect(client,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWrite(qint64)));
	connect(client,SIGNAL(disconnected()),this,SLOT(disconnectClient()));
	//qDebug() << "connected";
}

void MadNet::disconnectClient(){
	server.listen(QHostAddress::Any,7777);
	emit stopWorking();
}

void MadNet::sendBuffer(QByteArray *buffer) {
		

	int result=client->write(buffer->data(),buffer->size());
	//qDebug() << "net" << QThread::currentThread();
		//if (result==-1) emit error();
		//  emit sendDone();
		delete buffer;

}
