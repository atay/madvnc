#include <QtCore>
#include <QApplication>
#include "MadServer.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MadServer madServer;
	return a.exec();

}
