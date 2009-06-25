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

class MadPix: public QThread {
Q_OBJECT

public:
	MadPix();
	void run();
	void stop();

public slots:
	void grab();

signals:
	void sendPix(QPixmap &pixmap);

private:
	QPixmap pixmap;
	volatile bool stopped;
};

#endif /* MADPIX_H_ */
