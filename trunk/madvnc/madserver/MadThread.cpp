#include "MadThread.h"
#include <QMetaType>

MadThread::MadThread(){
	madNet = new MadNet();
	madShooter= new MadShooter();
	
	timer.setInterval(1000);
	timer.setSingleShot(false);
	timer1.setInterval(10000);
	timer1.setSingleShot(false);
}
void MadThread::run(){
	madWorker = new MadWorker();
	connect(&timer1,SIGNAL(timeout()),this,SLOT(stats()));

	qRegisterMetaType<QImage>("QImage&");
	connect(this,SIGNAL(startShooting()),madShooter,SLOT(makeScreenShoot()),Qt::QueuedConnection);
	connect(madWorker,SIGNAL(nextPlease()),madShooter,SLOT(makeScreenShoot()),Qt::QueuedConnection);
	connect(madShooter,SIGNAL(sendImage(QImage&,QImage&)),madWorker,SLOT(getImage(QImage&,QImage&)),Qt::QueuedConnection);
	connect(madWorker,SIGNAL(sendBuffer(QByteArray*)),madNet,SLOT(sendBuffer(QByteArray*)),Qt::QueuedConnection);	
	connect(madNet,SIGNAL(stopWorking()),madWorker,SLOT(stopingWorking()));
	connect(madNet,SIGNAL(stopWorking()),madShooter,SLOT(stopingWorking()));
	QObject::connect(madNet,SIGNAL(connectionStart()),this,SLOT(startGrab()));
	exec();
}

void MadThread::startGrab(){
	madWorker->stoped=false;
	madShooter->stoped=false;
	emit startShooting();
	
	timer1.start();
}
void MadThread::stats(){
	qDebug() << madShooter->count;
	madShooter->count=0;
}