/*
 * main.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include "MadServer.h"
#include "MadPix.h"

int main(int argc, char *argv[]){
	MadServer madserver;
	MadPix madpix;

	QApplication a(argc, argv);

	QObject::connect (&madserver, SIGNAL(connectionStart()),&madpix,SLOT(grab()));
	QObject::connect (&madpix,SIGNAL(sendPix(QPixmap &pixmap)),&madserver,SLOT(sendWindow(QPixmap &qpix)));
	return a.exec();
}
