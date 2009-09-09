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
#include <QtGui>




class MadServer: public QWidget{
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
	MadThread madThread;
	QSystemTrayIcon *trayIcon;
	QAction *quitAction,*disconnectAction,*onOffAction,*addressAction;
	QMenu *trayIconMenu;
	QIcon icon;

};

#endif /* MADSERVER_H_ */
