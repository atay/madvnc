/*
 * MadPix.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#include "MadPix.h"
#include <QtCore>
#include <QApplication>
#include <QtGui>

MadPix::MadPix(){
	stopped=false;
}
void MadPix::grab() {
	start();
}

void MadPix::run() {
	while (!stopped) {
		pixmap = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
				QSize(300,300), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		emit sendPix(pixmap);
	}
}

void MadPix::stop(){
	stopped=true;
}
