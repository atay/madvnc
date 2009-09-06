/*
 * MadShooter.h
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#ifndef MADSHOOTER_H_
#define MADSHOOTER_H_
#include <QThread>
#include <QPixmap>

class MadShooter: public QObject{
Q_OBJECT
public:
	MadShooter();
	

protected:
	void run();

signals:
	void sendImage(QImage&,QImage&);

public slots:
		void makeScreenShoot();

public:
	volatile int count;
private:
	QImage img1,img2;
	
};

#endif /* MADSHOOTER_H_ */
