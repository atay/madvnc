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

	stopButton = new QPushButton("Stop");
	stopButton->setEnabled(true);

	QHBoxLayout *buttons = new QHBoxLayout;

	buttons->addWidget(startButton);
	buttons->addWidget(sendButton);
	buttons->addWidget(stopButton);

	label = new QLabel;
	label->setMinimumSize(300, 300);
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(startButton, SIGNAL(clicked()), this, SLOT(startConnection()));
	connect(&socket, SIGNAL(readyRead()), this, SLOT(drawWindow()));
	connect(stopButton, SIGNAL(clicked()), this, SLOT(close()));

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

void MadSocket::keyPressEvent(QKeyEvent* event)
{
	qDebug("key: %d", event->key());
}

void MadSocket::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		qDebug("Pressed at: (%d x %d)", event->pos().x(), event->pos().y());
		pressed = true;
	}
}

void MadSocket::wheelEvent(QWheelEvent *event)
{
		qDebug("SCROLL: %d", event->delta());

}

void MadSocket::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && pressed) {
		qDebug("Released at: (%d x %d)", event->pos().x(), event->pos().y());
		pressed = false;
	}
}

void MadSocket::mouseMoveEvent(QMouseEvent *event)
 {
     if (pressed)
    	 qDebug("Moving at: (%d x %d)", event->x(), event->y());
 }
