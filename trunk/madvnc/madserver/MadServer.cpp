#include "MadServer.h"

MadServer::MadServer(){
	
	timer.setInterval(50);
	timer.setSingleShot(false);

	madNet.start();
	madShooter.start();
	connect(&timer,SIGNAL(timeout()),&madShooter,SLOT(makeScreenShot()));
	connect(&madShooter,SIGNAL(sendBuffer(QByteArray*)),&madNet,SLOT(sendBuffer(QByteArray*)),Qt::QueuedConnection);	
	
	QObject::connect(&madNet,SIGNAL(connectionStart()),this,SLOT(startGrab()));
	

}

void MadServer::startGrab(){
	timer.start();
}