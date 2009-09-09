#include "MadTray.h"


MadTray::MadTray(){
	
	trayIconMenu = new QMenu(this);
	//   trayIconMenu->addAction(restoreAction);
	quitAction = new QAction(trUtf8("&Close"), this);
	disconnectAction = new QAction(trUtf8("&Disconnect"), this);
	disconnectAction->setDisabled(true);
	onOffAction = new QAction(trUtf8("&Suspend"), this);
	onOffAction->setCheckable(true);
	addressAction = new QAction(trUtf8("Not Connected"), this);
	addressAction->setDisabled(true);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
	//connect(disconnectAction, SIGNAL(triggered()), th, SLOT(quit()));
	trayIconMenu->addAction(addressAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(onOffAction);
	trayIconMenu->addAction(disconnectAction);
	trayIconMenu->addAction(quitAction);
	
	


	trayIcon = new QSystemTrayIcon(this);
	cIcon = new QIcon("images/on.png");
	dIcon = new QIcon("images/off.png");
	sIcon = new QIcon("images/suspend.png");
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(*dIcon);
	trayIcon->setVisible(true);
}

void MadTray::showTrayTooltip(const QString &title, const QString &msg){
	trayIcon->showMessage(title,msg);
}
void MadTray::connectionStarted(const QString & address){
	trayIcon->showMessage("Client connected","Client from address: " + address + " was connected successfully!");
	trayIcon->setIcon(*cIcon);
	disconnectAction->setEnabled(true);
}
void MadTray::stopingWorking(){
	trayIcon->setIcon(*dIcon);
	trayIcon->showMessage("Client disconnected","Client was connected successfully!");
}