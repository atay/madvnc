/*
 * MadWorker.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADWORKER_H_
#define MADWORKER_H_
#include <QObject>
#include <QImage>



class MadWorker: public QObject {
Q_OBJECT

public:
	static const qint16 ALL_PIC=1000000;
	MadWorker();

public slots:
	void getScreen(QImage);

signals:
	void sendBuffer(QByteArray &);

private:
	QImage oldimg;

};

#endif /* MADWORKER_H_ */
