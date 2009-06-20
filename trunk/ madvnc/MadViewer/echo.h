/*
 * echo.h
 *
 *  Created on: 2009-06-19
 *      Author: dziq
 */


#ifndef ECHO_H_
#define ECHO_H_
#include <QDialog>
#include <QTcpSocket>
#include <QTcpServer>
class QPushButton;
class QLineEdit;
class QTextEdit;
class QTcpSocket;
class QTcpServer;
class QLabel;

class Echo: public QDialog {
Q_OBJECT

public:
	Echo(QWidget *parent = 0);

public slots:
	void startConnection();
	void prepareClient();
	void sendWindow();
	void drawWindow();
	//void send();

private:
	QPushButton *startButton,*sendButton;
	QLineEdit *toSend;
	QTextEdit *rec;
	QTcpSocket socket;
	QTcpSocket *client;
	QTcpServer server;
	QLabel *label;
	QLabel *log;


};


#endif /* ECHO_H_ */
