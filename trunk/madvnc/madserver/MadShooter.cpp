/*
 * MadShooter.cpp
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#include "MadShooter.h"
#include <QtGui>


MadShoter::MadShoter(){
}

void MadShoter::makeScreenShot(){


	img = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
	emit newScreen(img);

}

