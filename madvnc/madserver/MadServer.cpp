#include "MadServer.h"

MadServer::MadServer(){



	
	thread1.start();

	

	
	
	//QObject::connect(&madNet,SIGNAL(connectionStart()),this,SLOT(startGrab()));
	

}

void MadServer::startGrab(){
	timer.start();

	timer1.start();
}
void MadServer::stats(){
	qDebug() << madShooter->count/5;
	madShooter->count=0;
}
