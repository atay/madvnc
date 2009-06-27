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
	void MadSocket::mousePressEvent(QMouseEvent *event);
	void MadSocket::mouseReleaseEvent(QMouseEvent *event);
	void MadSocket::mouseMoveEvent(QMouseEvent *event);
	void MadSocket::wheelEvent(QWheelEvent *event);
	void MadSocket::keyPressEvent(QKeyEvent * event);


public slots:
	void startConnection();
	void drawWindow();
	//void send();

private:
	QPushButton *startButton, *sendButton, *stopButton;
	QTcpSocket socket;
	QLabel *label;
	quint16 nextBlock;
	bool pressed;
};

#endif /* MADSOCKET_H_ */
