/*
 * MadSocket.cpp
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */
#include "QtGui"
#include "QtNetwork"
#include "MadSocket.h"

MadSocket::MadSocket(QWidget * parent) :
	QDialog(parent) {

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

	connect(startButton, SIGNAL(clicked()), this, SLOT(startConnection()));

	connect(&socket, SIGNAL(readyRead()), this, SLOT(drawWindow()));

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addLayout(buttons);
	setLayout(layout);
	setFixedHeight(sizeHint().height());
	nextBlock = 0;
}

void MadSocket::startConnection() {
	socket.connectToHost(QHostAddress::LocalHost, 7777);
	qDebug("trying to connect...");
}

void MadSocket::drawWindow() {
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
	}
	if (socket.bytesAvailable() < nextBlock)
		return;

	stream >> qpix;

	label->setPixmap(qpix);
	nextBlock = 0;
}
