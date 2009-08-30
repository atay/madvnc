/*
 * MadPix.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADPIX_H_
#define MADPIX_H_
#include <QObject>
#include <QPixmap>
#include <QThread>
#include "ScreenShooter.h"

class MadPix: public QThread {
Q_OBJECT

public:
	MadPix();
	void run();
	void stop();
	void setScreenShoter(ScreenShoter * ss){
		screenShoter=ss;
	}

public slots:
	void grab();
	void preparePixmap(QPixmap);


signals:
	void sendPix(QPixmap pixmap);

private:
	QPixmap pixmap;
	volatile bool stopped;
	ScreenShoter *screenShoter;

};

#endif /* MADPIX_H_ */
