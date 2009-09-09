#include "MadServer.h"

MadServer::MadServer(){
	
	timer.setInterval(1000);
	timer.setSingleShot(false);
	testt.setInterval(5000);
	testt.setSingleShot(false);

	madNet.start();
	madShooter.start();
	connect(&timer,SIGNAL(timeout()),&madShooter,SLOT(makeScreenShot()));
	connect(&testt,SIGNAL(timeout()),&madShooter,SLOT(showcount()));
	connect(&madShooter,SIGNAL(sendBuffer(QByteArray*)),&madNet,SLOT(sendBuffer(QByteArray*)),Qt::QueuedConnection);	
	
	QObject::connect(&madNet,SIGNAL(connectionStart()),this,SLOT(startGrab()));
	

}

void MadServer::startGrab(){
	timer.start();
	testt.start();
}