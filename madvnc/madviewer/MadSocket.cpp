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
	label->setMinimumSize(700, 700);
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(startButton, SIGNAL(clicked()), this, SLOT(startConnection()));

	connect(&socket, SIGNAL(readyRead()), this, SLOT(drawWindow()));

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(label);
	layout->addLayout(buttons);
	setLayout(layout);
	setFixedHeight(sizeHint().height());
	nextBlock = 0;
	img = QImage(1280,800,QImage::Format_RGB32);	
}

void MadSocket::startConnection() {
	socket.connectToHost("192.168.56.1", 7777);
	qDebug() << "madviewer -> trying to connect";

}

void MadSocket::drawWindow() {
	quint16 lines2read,line;
	uint bytesperline;
	QByteArray buffer;
	char *temp;
	uint len;
	QDataStream stream(&socket);
	stream.setVersion(QDataStream::Qt_4_1);

	if (nextBlock == 0) {
		if (socket.bytesAvailable() < sizeof(quint64))
			return;
		stream >> nextBlock;
	}
	if (socket.bytesAvailable() < nextBlock)
		return;
	
	stream >> lines2read;

	if (lines2read==ALL_PIC){
		len=uint(nextBlock);
		stream.readBytes(temp,len);
		memcpy(img.bits(),temp,len);
		delete [] temp;
	} else {
		stream >> bytesperline;
		for (int i=0;i<lines2read;i++){
			stream >> line;
			stream.readBytes(temp,bytesperline);
			memcpy(img.scanLine(line),temp,bytesperline);
			delete [] temp;

		}
	}

	label->setPixmap(QPixmap::fromImage(img));
	nextBlock = 0;

}
