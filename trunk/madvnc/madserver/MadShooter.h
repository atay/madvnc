/*
 * MadShooter.h
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#ifndef MADSHOOTER_H_
#define MADSHOOTER_H_
#include <QObject>
#include <QPixmap>

class MadShoter: public QObject{
Q_OBJECT
public:
	MadShoter();


private slots:
	void makeScreenShot();


signals:
	void newScreen(QImage);

public:
	
private:
	QImage img;
	bool ready;
};

#endif /* MADSHOOTER_H_ */
