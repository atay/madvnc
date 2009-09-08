/*
* MadServer.cpp
*
*  Created on: 2009-06-25
*      Author: dziq
*/
#include "MadNet.h"
#include <QtGui>
#include <windows.h>

void Click(int);

MadNet::MadNet(){
	server.listen(QHostAddress::Any,7777);
	connect(&server,SIGNAL(newConnection()),this,SLOT(prepareClient()));
	nextBlock=0;
}

void MadNet::bytesWrite(qint64 size){

}
void MadNet::prepareClient() {
	client = server.nextPendingConnection();
	server.close();
	emit connectionStart();
	connect(client,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWrite(qint64)));
	connect(client,SIGNAL(disconnected()),this,SLOT(disconnectClient()));
	qDebug() << "connected";

	// do odbierania glupot od klienta
	connect(client, SIGNAL(readyRead()), this, SLOT(receiveControls()));

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

void MadNet::receiveControls(){

	// wesola nowina - dane z myszy i klawiatury przychodza jak nalezy, ale tak
	// szybko ze ponizsze rozwiazanie nie jest wystarczajace - w strumieniu
	// zostaja sockecie client zostaja dane i wychodza z opoznieniem, sie wszystko
	// pierniczy, a client->bytesAvailable() rosnie coraz bardziej
	// milej zabawy
	QDataStream controls(client);
	controls.setVersion(QDataStream::Qt_4_1);

	if (nextBlock == 0) {
		if (client->bytesAvailable() < sizeof(quint16))
			return;
		controls >> nextBlock;
	}
	if (client->bytesAvailable() < nextBlock)
		return;
	quint64 type,button, buttons,modifiers;
	quint16 x,y;

	//controls >> type >> x >> y >> button >> buttons >> modifiers;
	controls >> x >> y;
			INPUT Input; 
			memset(&Input, 0, sizeof(INPUT)); 
	type=QEvent::MouseMove;
	switch (type){
		case QEvent::MouseMove:
			qDebug() << "mose move: x:" << x << ", y: " << y;
			SetCursorPos((int)x,(int)y);
			break;
		case QEvent::MouseButtonPress:

			Input.type = INPUT_MOUSE; 
			if (button==Qt::LeftButton)
				Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; 
			else if (button==Qt::RightButton)
				Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; 
			SendInput(1, &Input, sizeof(INPUT)); 
			break;
		case QEvent::MouseButtonRelease:

			Input.type = INPUT_MOUSE; 
			if (button==Qt::LeftButton)
				Input.mi.dwFlags = MOUSEEVENTF_LEFTUP; 
			else if (button==Qt::RightButton)
				Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; 
			SendInput(1, &Input, sizeof(INPUT)); 
			break;
	}


	//QApplication::postEvent(QApplication::desktop(), &myEvent);

	nextBlock=0;
}
void Click(int ClickSpeed) 
{ 

	INPUT Input; 
	memset(&Input, 0, sizeof(INPUT)); 
	Input.type = INPUT_MOUSE; 
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; 
	SendInput(1, &Input, sizeof(INPUT)); 
	Sleep(ClickSpeed); 
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP; 
	SendInput(1, &Input, sizeof(INPUT)); 
	Sleep(ClickSpeed); 
}