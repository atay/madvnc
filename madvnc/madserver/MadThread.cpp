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

	connect(madNet,SIGNAL(connectionStart(const QString &)),this,SLOT(startGrab()));
	connect(madNet,SIGNAL(connectionStart(const QString &)),&madTray,SLOT(connectionStarted(const QString &)));

	connect(&madTray,SIGNAL(stopWorking()),madShooter,SLOT(stopingWorking()));
	connect(&madTray,SIGNAL(stopWorking()),madWorker,SLOT(stopingWorking()));
	connect(&madTray,SIGNAL(stopWorking()),madNet,SLOT(stopingWorking()));
	connect(&madTray,SIGNAL(stopWorking()),this,SLOT(stopingWorking()));
	
	connect(madNet,SIGNAL(stopWorking()),&madTray,SLOT(stopingWorking()));
	connect(madNet,SIGNAL(stopWorking()),madWorker,SLOT(stopingWorking()));
	connect(madNet,SIGNAL(stopWorking()),madShooter,SLOT(stopingWorking()));
	connect(madNet,SIGNAL(stopWorking()),this,SLOT(stopingWorking()));
	
	exec();
}

void MadThread::startGrab(){
	madWorker->stoped=false;
	madShooter->stoped=false;
	emit startShooting();
	timer1.start();
}

void MadThread::stopingWorking(){
	timer1.stop();
	timer.stop();
}
void MadThread::stats(){
	qDebug() << madShooter->count;
	madShooter->count=0;
}

