#include "MadServer.h"

MadServer::MadServer(){
	
	madThread.start();
}

void MadServer::startGrab(){
	timer.start();
	timer1.start();
}
void MadServer::stats(){
	qDebug() << madShooter->count/5;
	madShooter->count=0;
}
