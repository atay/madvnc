/*
 * MadPix.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#include "MadPix.h"
#include <QtGui>

MadPix::MadPix() {

	stopped = false;
	qDebug("MadPix created");
}

void MadPix::grab() {
	start();
	screenShoter->timer.start();
	qDebug("grab started");
}

void MadPix::preparePixmap(QPixmap pixmap){
	emit sendPix(pixmap);
}
void MadPix::run() {

	connect(screenShoter,SIGNAL(newPixmap(QPixmap)),this,SLOT(preparePixmap(QPixmap)));

	exec();
}

void MadPix::stop() {
	stopped = true;
}
