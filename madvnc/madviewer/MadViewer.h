#ifndef MADVIEWER_H_
#define MADVIEWER_H_

#include <QtGui>
#include <QtNetwork>

class MadViewer: public QDialog {

	Q_OBJECT

public:

	static const qint16 ALL_PIC=1000000;
	MadViewer(QWidget *parent = 0);

public slots:

	void startConnection();
	void enableConnectButton();
	void changeConnectButton();
	void drawWindow();
	//void send();

private:
	QPushButton *connectButton, *sendButton, *exitButton;
	QLineEdit *addressEdit;
	QLabel *addressLabel, *mainViewLabel;
	QTcpSocket socket;
	quint64 nextBlock;
	QImage img;

};


#endif /* MADVIEWER_H_ */
