/*
 * MadSocket.h
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#ifndef MADSOCKET_H_
#define MADSOCKET_H_

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
class QPushButton;
class QLineEdit;
class QTextEdit;
class QTcpSocket;
class QLabel;

class MadSocket: public QDialog {
Q_OBJECT

public:
	MadSocket(QWidget *parent = 0);

public slots:
	void startConnection();
	void drawWindow();
	//void send();

private:
	QPushButton *startButton,*sendButton;
	QTcpSocket socket;
	QLabel *label;
	quint16 nextBlock;


};


#endif /* MADSOCKET_H_ */
