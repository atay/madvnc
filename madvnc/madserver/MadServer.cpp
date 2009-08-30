#include "MadServer.h"

MadServer::MadServer(){
	
	timer.setInterval(25);
	timer.setSingleShot(false);

	connect(&timer,SIGNAL(timeout()),&madShoter,SLOT(makeScreenShot()));
	connect(&madShoter,SIGNAL(newScreen(QImage)),&madWorker,SLOT(getScreen(QImage)));
	connect(&madWorker,SIGNAL(sendBuffer(QByteArray &)),&madNet,SLOT(sendBuffer(QByteArray &)));	
	
	QObject::connect(&madNet,SIGNAL(connectionStart()),this,SLOT(startGrab()));


}

void MadServer::startGrab(){
	timer.start();
}