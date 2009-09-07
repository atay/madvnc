/*
 * MadWorker.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADWORKER_H_
#define MADWORKER_H_

#include <QImage>



class MadWorker: public QObject{
Q_OBJECT

public:
	static const qint16 ALL_PIC=1000000;
	static const qint16 PODZIAL=16;
	MadWorker();

public slots:
	void getImage(QImage&,QImage&);
	void stopingWorking();

signals:
	void sendBuffer(QByteArray*);
	void nextPlease();
	

public:
	QImage *oldimg;
	QByteArray *buffer;
	bool stoped;


};

#endif /* MADWORKER_H_ */
