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
#include <QTimer>




class MadServer: public QObject{
Q_OBJECT

public:
	MadServer();

public slots:
	void startGrab();

signals:
	

private:
	MadShoter madShoter;
	MadNet madNet;
	MadWorker madWorker;
	QTimer timer;

};

#endif /* MADSERVER_H_ */
