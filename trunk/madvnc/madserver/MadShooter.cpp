/*
* MadShooter.cpp
*
*  Created on: 2009-06-26
*      Author: dziq
*/

#include "MadShooter.h"
#include <QtGui>


MadShooter::MadShooter(){
	count=0;
}
void MadShooter::makeScreenShoot(){
	if ((count%2)==0){
		img1 = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
                        QSize(1024, 640), Qt::KeepAspectRatio, Qt::SmoothTransformation).toImage();
		emit sendImage(img1,img2);

	} else {
		img2 = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
                        QSize(1024, 640), Qt::KeepAspectRatio, Qt::SmoothTransformation).toImage();
		emit sendImage(img2,img1);
	}
		count++;
		//qDebug() << "shooter" << QThread::currentThread();
}
void MadShooter::stopingWorking(){
	img1=QImage();
	img2=QImage();
	qDebug() << "shooter stoped";
}