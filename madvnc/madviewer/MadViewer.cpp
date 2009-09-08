#include <QtGui>
#include <QtNetwork>
#include "MadViewer.h"

MadViewer::MadViewer(QWidget * parent) : QDialog(parent) {

    madNet.start();
    isConnected = false;

    connectButton = new QPushButton("Connect");
    connectButton->setEnabled(true);    // odblokowany bo startujemy z wypelnionym polem adresu
    //connectButton->setDefault(true);

    exitButton = new QPushButton("E&xit");
    exitButton->setEnabled(true);

    addressEdit = new QLineEdit("192.168.137.1");
    addressLabel = new QLabel("MadServer &address :");
	statusLabel = new QLabel("App started");
    addressLabel->setBuddy(addressEdit);

    QHBoxLayout *controls = new QHBoxLayout;

    controls->addWidget(addressLabel);
    controls->addWidget(addressEdit);
    controls->addWidget(connectButton);
    controls->addWidget(exitButton);

    connect(addressEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableConnectButton()));
    connect(connectButton, SIGNAL(clicked()), this, SLOT( manageClicked() ));
    connect(exitButton, SIGNAL(clicked()), this , SLOT(close() ) );

    mainViewLabel = new QLabel(this);
    mainViewLabel->setMinimumSize(1280,800);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mainViewLabel);
    layout->addLayout(controls);
	layout->addWidget(statusLabel);
    setLayout(layout);

    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    connect(&madNet.socket, SIGNAL(readyRead()),     this, SLOT(drawImage()));
    connect(&madNet.socket, SIGNAL(connected()),     this, SLOT(connectedToServer()));
    connect(&madNet.socket, SIGNAL(disconnected()),  this, SLOT(disconnectedFromServer()));
	connect(this, SIGNAL(newMouseEvent(QMouseEvent)),  &madNet, SLOT(sendMouseEvent(QMouseEvent)));
	connect(this, SIGNAL(newKeyEvent(QMouseEvent)),  &madNet, SLOT(sendKeyEvent(QMouseEvent)));
	connect(this, SIGNAL(newWheelEvent(QMouseEvent)),  &madNet, SLOT(sendWheelEvent(QMouseEvent)));
    //connect(&madNet.socket, SIGNAL(error(SocketError &)),this, SLOT(connectionError(QAbstractSocket::SocketError socketError)));

    nextBlock = 0;
    img = QImage(1280,800,QImage::Format_RGB16);

}

void MadViewer::disconnectedFromServer(){
    mainViewLabel->setText("Connection finished..");
    connectButton->setText("Connect");
    isConnected = false;
    setMouseTracking(false);
	mainViewLabel->setMouseTracking(false);

}
void MadViewer::connectedToServer(){
    qDebug("connected");
    mainViewLabel->setText("Connection estabilished..");
    connectButton->setText("Disconnect");
    //connectButton->setEnabled(true);
    isConnected = true;
    setMouseTracking(true);
	mainViewLabel->setMouseTracking(true);

}

void MadViewer::manageClicked() {
    if(!isConnected)
    {
        //connectButton->setEnabled(false);
        qDebug("connecting..");
        mainViewLabel->setText("Connecting to " + addressEdit->text());
        madNet.connect(addressEdit->text());
    }
    else
    {
        qDebug("disconnecting..");
        madNet.disconnect();
    }
}

void MadViewer::enableConnectButton() {

    connectButton->setEnabled( !addressEdit->text().isEmpty() );
}

// --- obraz

void MadViewer::drawImage() {
	quint16 lines2read,line;
	uint bytesperline;
	QByteArray buffer;
	char *temp;
	uint len;
	QDataStream stream(&madNet.socket);//&socket);
	stream.setVersion(QDataStream::Qt_4_1);

	if (nextBlock == 0) {
		if (madNet.socket.bytesAvailable() < sizeof(quint64))
			return;
		stream >> nextBlock;
	}
	if (madNet.socket.bytesAvailable() < nextBlock)
		return;
	
	stream >> lines2read;

	quint16 ilosc = img.height()/PODZIAL;
	quint16 bpl = img.bytesPerLine();
	QImage tempimg = QImage(1280,ilosc,QImage::Format_ARGB32);

	if (lines2read==ALL_PIC){
		stream >> img;
	} else {
		for (int i=0;i<lines2read;i++){
			stream >> line;
			stream >> tempimg;
			memcpy(img.bits()+line*ilosc*bpl,tempimg.bits(),bpl*ilosc);
		}
	}

	mainViewLabel->setPixmap(QPixmap::fromImage(img));
	nextBlock = 0;

}

// --- mysz i klawiatura

void MadViewer::sendControls(quint16 eventType, quint16 eventData1, quint16 eventData2) {

    QByteArray controls;
    QDataStream controlStream(&controls, QIODevice::ReadWrite);
    controlStream.setVersion(QDataStream::Qt_4_1);

    controlStream << quint16(sizeof(quint16)*3);
    controlStream << eventType << eventData1 << eventData2;

    //controlStream.device()->reset();
    //controlStream << (quint16)(controls.size() - sizeof(quint16));
    QTcpSocket * serwer = &madNet.socket;
    //serwer->write(controls);

}

void MadViewer::mouseMoveEvent(QMouseEvent *event) {
	statusLabel->setText(QString("mouse move: x: "+QString::number(event->pos().x())+", y: "+QString::number(event->pos().y())));
	
	emit newMouseEvent(*event);
}

void MadViewer::mousePressEvent(QMouseEvent *event)
{
	emit newMouseEvent(*event);
}

void MadViewer::mouseReleaseEvent(QMouseEvent *event)
{
	emit newMouseEvent(*event);
}

void MadViewer::wheelEvent(QWheelEvent *event)
{
    emit newWheelEvent(*event);
}

void MadViewer::keyPressEvent(QKeyEvent* event)
{
    emit newKeyEvent(*event);
}

void MadViewer::keyReleaseEvent(QKeyEvent* event)
{
    emit newKeyEvent(*event);
}

/*
  proponuje taki protokol sterowania:

sendControls(quint16 eventType, quint16 eventData1, quint16 eventData2)

ruch myszy:
    eventType   1
    eventData1  polozenieX ( >= 0 )
    eventData2  polozenieY ( >= 0 )

klikniecie:
    eventType   2
    eventData1  1 - lewy przycisk, 2 - prawy przycisk itd..
    eventData2  1 - wcisniecie, 2 - zwolnienie

obrot kolka:
    eventType   3
    eventData1  kat obrotu (+/- 120)
    eventData2  plaszczyzna (1 - vertical, 2 - horizontal)

klawiatura:
    eventType   4
    eventData1  kod klawisza (event->key)
    eventData2  1 - wcisniecie 2- zwolnienie
*/
