/*
 * MadShooter.h
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#ifndef MADTHREAD_H_
#define MADTHREAD_H_
#include <QThread>
#include <QTimer>
#include "MadShooter.h"
#include "MadNet.h"
#include "MadWorker.h"
#include "MadTray.h"

class MadThread: public QThread{
Q_OBJECT
public:
	MadThread();
	QThread * thread;
	MadShooter * madShooter;
	MadNet *madNet;
	MadWorker * madWorker;
	QTimer timer, timer1;
	MadTray madTray;
protected:
	void run();
signals:
	void startShooting();
	void stopWorking();
public slots:
	void startGrab();
	void stopingWorking();
	void stats();
};
#endif 
