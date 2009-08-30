/*
 * ScreenShooter.h
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#ifndef SCREENSHOOTER_H_
#define SCREENSHOOTER_H_
#include <QObject>
#include <QTimer>
#include <QPixmap>

class ScreenShoter: public QObject{
Q_OBJECT
public:
	ScreenShoter();


private slots:
	void makeScreenShot();


signals:
	void newPixmap(QPixmap);

public:
	QTimer timer;
private:
	QPixmap pixmap;
};

#endif /* SCREENSHOOTER_H_ */
