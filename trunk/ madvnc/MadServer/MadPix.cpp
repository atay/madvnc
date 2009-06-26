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
	connect(this,SIGNAL(makePix()),this,SLOT(makeScreenshot()));

}
void MadPix::grab() {
	start();
	qDebug("grab started");
}
void MadPix::makeScreenshot(){
	pixmap = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
			QSize(300, 300), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void MadPix::run() {
	while (!stopped) {
		emit makePix();
		sleep(1);

		emit sendPix(pixmap);

		qDebug("sendPix emited");
	}
}

void MadPix::stop() {
	stopped = true;
}
