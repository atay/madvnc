/*
 * echo.cpp
 *
 *  Created on: 2009-06-19
 *      Author: dziq
 */
#include <QtGui>
#include <QtNetwork>
#include <stdio.h>
#include "echo.h"

Echo::Echo(QWidget *parent) :
	QDialog(parent) {

	server.listen(QHostAddress::LocalHost, 7777);
	server.setMaxPendingConnections(1);

	startButton = new QPushButton(tr("Connect"));
	startButton->setEnabled(true);
	startButton->setDefault(true);
	sendButton = new QPushButton(tr("Grab!!"));
	sendButton->setEnabled(false);
	QHBoxLayout *buttons = new QHBoxLayout;
	buttons->addWidget(startButton);
	buttons->addWidget(sendButton);
	label = new QLabel;
	label->setMinimumSize(300,300);
	label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	log = new QLabel;
	log->setText("App started");
	connect(startButton,SIGNAL(clicked()),this,SLOT(startConnection()));
	connect(&server,SIGNAL(newConnection()),this,SLOT(prepareClient()));
	connect(&socket,SIGNAL(readyRead()),this,SLOT(drawWindow()));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(log);
	layout->addLayout(buttons);
	setLayout(layout);
	setFixedHeight(sizeHint().height());
}
void Echo::startConnection() {
	socket.connectToHost(QHostAddress::LocalHost, 7777);
}


void Echo::prepareClient() {
	client = server.nextPendingConnection();
	sendButton->setEnabled(true);
	connect(sendButton,SIGNAL(clicked()),this,SLOT(sendWindow()));
	server.close();

}
void Echo::sendWindow(){
	QPixmap qpix = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

	QDataStream stream(client);
	stream << qpix;
	log->setText("Windows send");
}

void Echo::drawWindow(){
	QPixmap qpix;
	QByteArray array;
	QDataStream stream(&socket);

	stream >> qpix;

	QString temp;
	if (array.size()==0)
		temp="array is empty";
	else
		temp=array.size();


	log->setText(temp);
	label->setPixmap(qpix);

}
