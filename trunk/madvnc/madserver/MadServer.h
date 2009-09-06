/*
 * MadServer.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADSERVER_H_
#define MADSERVER_H_
#include <QObject>
#include "MadNet.h"
#include "MadWorker.h"
#include "MadShooter.h"
#include "MadThread.h"
#include <QTimer>




class MadServer: public QObject{
Q_OBJECT

public:
	MadServer();

public slots:
	void startGrab();
	void stats();

signals:
	

private:
	MadShooter *madShooter;
	MadNet *madNet;
	QTimer timer,timer1;
	MadThread thread1,thread2;

};

#endif /* MADSERVER_H_ */
