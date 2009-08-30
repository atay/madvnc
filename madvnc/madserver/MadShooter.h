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

private slots:
	void makeScreenShot();
protected:
	void run();

signals:
	void sendBuffer(QByteArray*);

public:
	
private:
	QImage img,oldimg;
	
	QByteArray *buffer;
};

#endif /* MADSHOOTER_H_ */
