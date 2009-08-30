#include <QtCore>
#include <QApplication>
#include "MadServer.h"
#include "MadPix.h"
#include "ScreenShooter.h"
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	qDebug() << "App started";
	MadServer madserver;
	MadPix madpix;
	ScreenShoter screenShoter;
	madpix.setScreenShoter(&screenShoter);

	QObject::connect(&madserver,SIGNAL(connectionStart()),&madpix,SLOT(grab()));
	QObject::connect(&madpix,SIGNAL(sendPix(QPixmap)),&madserver,SLOT(sendWindow(QPixmap)));
	return a.exec();

}
