/*
 * MadWorker.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADWORKER_H_
#define MADWORKER_H_
#include <QThread>
#include <QImage>

class QThread;

class MadWorker: public QThread {
Q_OBJECT

public:
	
	MadWorker();

	void run();
public slots:
	void getScreen(QImage);

signals:
	

private:


};

#endif /* MADWORKER_H_ */
