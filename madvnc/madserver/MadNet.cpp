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
	emit connectionStart(client->peerAddress().toString());
	
	connect(client,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWrite(qint64)));
	connect(client,SIGNAL(disconnected()),this,SLOT(disconnectClient()));
	qDebug() << "connected";

	// do odbierania glupot od klienta
	connect(client, SIGNAL(readyRead()), this, SLOT(receiveControls()));

}

void MadNet::stopingWorking(){
	if (client!=NULL) client->disconnect();
	server.listen(QHostAddress::Any,7777);
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

	while(client->bytesAvailable()>0){
		if (nextBlock == 0) {
			if (client->bytesAvailable() < sizeof(quint16))
				return;
			controls >> nextBlock;
		}
		if (client->bytesAvailable() < nextBlock)
			return;
		quint64 type,button, buttons,modifiers;
		QPoint point;

		controls >> type; 
		INPUT Input; 
		memset(&Input, 0, sizeof(INPUT)); 
		
		
		switch (type){
		case QEvent::MouseMove:
			controls >> point >> button >> buttons >> modifiers;
			SetCursorPos(point.x(),point.y());
			break;
		
		case QEvent::MouseButtonPress:
			controls >> point >> button >> buttons >> modifiers;

			Input.type = INPUT_MOUSE; 
			if (button==Qt::LeftButton)
				Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; 
			else if (button==Qt::RightButton)
				Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; 
			SendInput(1, &Input, sizeof(INPUT)); 
			break;
		 
		case QEvent::MouseButtonRelease:
			controls >> point >> button >> buttons >> modifiers;

			Input.type = INPUT_MOUSE; 
			if (button==Qt::LeftButton)
				Input.mi.dwFlags = MOUSEEVENTF_LEFTUP; 

			else if (button==Qt::RightButton)
				Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; 
			SendInput(1, &Input, sizeof(INPUT)); 
			break;

	
		case QEvent::KeyPress:
		case QEvent::KeyRelease:    
			controls >> button >> modifiers;

			
			
			switch(button)
			{
				case Qt::Key_Shift:
					Input.ki.wVk = VK_SHIFT;	
					break;
				case Qt::Key_Control:
					Input.ki.wVk = VK_CONTROL;	
					break;
				case Qt::Key_Alt:
					Input.ki.wVk = VK_RMENU;	
					break;
				case Qt::Key_Escape:
					Input.ki.wVk = VK_ESCAPE;	
					break;
				case Qt::Key_Backspace:
					Input.ki.wVk = VK_BACK;	
					break;
				case Qt::Key_Return:
					Input.ki.wVk = VK_RETURN;	
					break;
				case Qt::Key_Enter:
					Input.ki.wVk = VK_RETURN;	
					break;
				case Qt::Key_Insert:
					Input.ki.wVk = VK_INSERT;	
					break;
				case Qt::Key_Delete:
					Input.ki.wVk = VK_DELETE;	
					break;
				case Qt::Key_Home:
					Input.ki.wVk = VK_HOME;	
					break;
				case Qt::Key_End:
					Input.ki.wVk = VK_END;	
					break;
				case Qt::Key_Left:
					Input.ki.wVk = VK_LEFT;	
					break;
				case Qt::Key_Up:
					Input.ki.wVk = VK_UP;	
					break;
				case Qt::Key_Right:
					Input.ki.wVk = VK_RIGHT;	
					break;
				case Qt::Key_Down:
					Input.ki.wVk = VK_DOWN;	
					break;
				case Qt::Key_PageUp:
					Input.ki.wVk = VK_PRIOR;	
					break;
				case Qt::Key_PageDown:
					Input.ki.wVk = VK_NEXT;	
					break;
				case Qt::Key_CapsLock:
					Input.ki.wVk = VK_CAPITAL;	
					break;
				case Qt::Key_F1:
					Input.ki.wVk = VK_F1;	
					break;
				case Qt::Key_F2:
					Input.ki.wVk = VK_F2;	
					break;
				case Qt::Key_F3:
					Input.ki.wVk = VK_F3;	
					break;
				case Qt::Key_F4:
					Input.ki.wVk = VK_F4;	
					break;
				case Qt::Key_F5:
					Input.ki.wVk = VK_F5;	
					break;
				case Qt::Key_F6:
					Input.ki.wVk = VK_F6;	
					break;
				case Qt::Key_F7:
					Input.ki.wVk = VK_F7;	
					break;
				case Qt::Key_F8:
					Input.ki.wVk = VK_F8;	
					break;
				case Qt::Key_F9:
					Input.ki.wVk = VK_F9;	
					break;
				case Qt::Key_F10:
					Input.ki.wVk = VK_F10;	
					break;
				case Qt::Key_F11:
					Input.ki.wVk = VK_F11;	
					break;
				case Qt::Key_F12:
					Input.ki.wVk = VK_F12;	
					break;
				case Qt::Key_Space:
					Input.ki.wVk = VK_SPACE;
					break;
				case Qt::Key_Plus:
					Input.ki.wVk = VK_ADD;
					break;
				case Qt::Key_Comma:	 
					Input.ki.wVk = VK_OEM_COMMA;
					break;
				case Qt::Key_Minus:
					Input.ki.wVk = VK_SUBTRACT;
					break;
				case Qt::Key_Period:
					Input.ki.wVk = VK_OEM_PERIOD;
					break;
				case Qt::Key_Slash:
					Input.ki.wVk = VK_DIVIDE;
					break;
				case Qt::Key_Backslash:
					Input.ki.wVk = VK_BACK;
					break;
				case Qt::Key_Colon:
					Input.ki.wVk = VK_OEM_COMMA;
					break;

				default: 
					Input.ki.wVk = (byte)button;
			}
			qDebug() << button;

			Input.type = INPUT_KEYBOARD; 
			if(type == QEvent::KeyRelease) Input.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &Input, sizeof(INPUT)); 

			break;
		}




		nextBlock=0;
	}
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