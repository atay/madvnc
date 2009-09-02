#include <QtCore>
#include <QApplication>
#include "MadViewer.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MadViewer madViewer;
	madViewer.show();

	return app.exec();

}
