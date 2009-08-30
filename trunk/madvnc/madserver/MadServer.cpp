#include "MadServer.h"

MadServer::MadServer(){
	
	timer.setInterval(20);
	timer.setSingleShot(false);
	//madWorker.start();
	//madNet.start();
	connect(&timer,SIGNAL(timeout()),&madShooter,SLOT(makeScreenShot()));
	connect(&madShooter,SIGNAL(sendBuffer(QByteArray*)),&madNet,SLOT(sendBuffer(QByteArray*)),Qt::QueuedConnection);	
	
	QObject::connect(&madNet,SIGNAL(connectionStart()),this,SLOT(startGrab()));
	

}

void MadServer::startGrab(){
	timer.start();
}