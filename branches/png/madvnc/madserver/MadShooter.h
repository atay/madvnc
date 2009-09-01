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

class MadShooter: public QThread{
Q_OBJECT
public:
	MadShooter();
	static const qint16 ALL_PIC=1000000;
	static const int WIDTH=1280;
	static const int HEIGHT=800;
	static const int PODZIAL=8;
	static const int BPP=4;


public slots:
	void makeScreenShot();
	void showcount();
protected:
	void run();

signals:
	void sendBuffer(QByteArray*);

public:
	
private:
	int count;
	QImage img,oldimg,tempimg;
	volatile bool stop;
	QByteArray *buffer;
};

#endif /* MADSHOOTER_H_ */
