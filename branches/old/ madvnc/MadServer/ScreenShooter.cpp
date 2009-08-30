/*
 * ScreenShooter.cpp
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#include "ScreenShooter.h"
#include <QtGui>

ScreenShoter::ScreenShoter(){
	timer.setInterval(50);
	timer.setSingleShot(false);

	connect(&timer,SIGNAL(timeout()),this,SLOT(makeScreenShot()));
}

void ScreenShoter::makeScreenShot(){
	pixmap = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
			QSize(300, 300), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	emit newPixmap(pixmap);
}

