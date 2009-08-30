/*
 * echo.cpp
 *
 *  Created on: 2009-06-19
 *      Author: dziq
 */
#include <QtGui>
#include <QtNetwork>
#include <QtDebug>
#include "echo.h"
#include <iostream>

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
	label->setMinimumSize(300, 300);
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	log = new QLabel;
	log->setText("App started");
	connect(startButton, SIGNAL(clicked()), this, SLOT(startConnection()));
	connect(&server, SIGNAL(newConnection()), this, SLOT(prepareClient()));
	connect(&socket, SIGNAL(readyRead()), this, SLOT(drawWindow()));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addWidget(log);
	layout->addLayout(buttons);
	setLayout(layout);
	setFixedHeight(sizeHint().height());
	nextBlock = 0;
}
void Echo::startConnection() {
	socket.connectToHost(QHostAddress::LocalHost, 7777);
}

void Echo::prepareClient() {
	client = server.nextPendingConnection();
	sendButton->setEnabled(true);
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendWindow()));
	server.close();

}
void Echo::sendWindow() {
	QPixmap qpix =
			QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
					label->size(), Qt::KeepAspectRatio,
					Qt::SmoothTransformation);

	if (qpix.height() > 0) {
		QByteArray block;

		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_1);

		out << quint16(0);
		out << qpix;
		out.device()->seek(0);
		out << quint16(block.size() - sizeof(quint16));
		client->write(block);
		log->setText("Windows send");

	} else
		log->setText("Windows not send");
}

void Echo::drawWindow() {
	QPixmap qpix;
	QByteArray array;
	QDataStream stream(&socket);
	stream.setVersion(QDataStream::Qt_4_1);
	QString temp;



	if (nextBlock == 0) {
		temp = nextBlock;

		if (socket.bytesAvailable() < sizeof(quint16))
			return;
		stream >> nextBlock;
		temp = nextBlock;
		log->setText(temp);
	}
	if (socket.bytesAvailable() < nextBlock)
		return;

	stream >> qpix;

	if (qpix.height() < 1)
		temp = "blalba";
	else
		temp = QString::number(qpix.height());

	log->setText(temp);
	label->setPixmap(qpix);
	nextBlock = 0;
}
