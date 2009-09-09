
/*
 * MadServer.h
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */

#ifndef MADTRAY_H_
#define MADTRAY_H_

#include <QObject>
#include <QTimer>
#include <QtGui>


class MadTray: public QWidget{
Q_OBJECT

public:
	MadTray();

public slots:

	void showTrayTooltip(const QString&,const QString&);
	void stopingWorking();
	void connectionStarted(const QString &);
signals:
	void stopWorking();
	

private:


	QSystemTrayIcon *trayIcon;
	QAction *quitAction,*disconnectAction,*onOffAction,*addressAction;
	QMenu *trayIconMenu;
	QIcon *cIcon,*dIcon,*sIcon;

};

#endif /* MADTRAY_H_ */
