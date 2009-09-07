#include <QtGui>
#include <QtNetwork>
#include "MadViewer.h"

MadViewer::MadViewer(QWidget * parent) : QDialog(parent) {

    madNet.start();
    isConnected = false;

    connectButton = new QPushButton("Connect");
    connectButton->setEnabled(true);    // odblokowany bo startujemy z wypelnionym polem adresu
    connectButton->setDefault(true);

    exitButton = new QPushButton("E&xit");
    exitButton->setEnabled(true);

    addressEdit = new QLineEdit("localhost");
    addressLabel = new QLabel("MadServer &address :");
    addressLabel->setBuddy(addressEdit);

    QHBoxLayout *controls = new QHBoxLayout;

    controls->addWidget(addressLabel);
    controls->addWidget(addressEdit);
    controls->addWidget(connectButton);
    controls->addWidget(exitButton);

    connect(addressEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableConnectButton()));
    connect(connectButton, SIGNAL(clicked()), this, SLOT( manageClicked() ));
    connect(exitButton, SIGNAL(clicked()), this , SLOT(close() ) );

    mainViewLabel = new QLabel(tr("Welcome in MADVNC program.."));
    mainViewLabel->setMinimumSize(800,600);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mainViewLabel);
    layout->addLayout(controls);
    setLayout(layout);

    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    connect(&madNet.socket, SIGNAL(readyRead()),     this, SLOT(drawImage()));
    connect(&madNet.socket, SIGNAL(connected()),     this, SLOT(connectedToServer()));
    connect(&madNet.socket, SIGNAL(disconnected()),  this, SLOT(disconnectedFromServer()));
    //connect(&madNet.socket, SIGNAL(error(SocketError &)),this, SLOT(connectionError(QAbstractSocket::SocketError socketError)));

    nextBlock = 0;
    img = QImage(800,600,QImage::Format_RGB16);

}

void MadViewer::disconnectedFromServer(){
    mainViewLabel->setText("Connection finished..");
    connectButton->setText("Connect");
    isConnected = false;
}
void MadViewer::connectedToServer(){
    qDebug("connected");
    mainViewLabel->setText("Connection estabilished..");
    connectButton->setText("Disconnect");
    //connectButton->setEnabled(true);
    isConnected = true;
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
	QImage tempimg = QImage(1024,ilosc,QImage::Format_ARGB32);

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

void MadViewer::sendControls(quint16 command){

    QByteArray controls;
    QDataStream controlStream(&controls, QIODevice::ReadWrite);
    controlStream.setVersion(QDataStream::Qt_4_1);

    //controlStream << (quint16)0;
    controlStream << (quint16)command;


    //controlStream.device()->reset();
    //controlStream << (quint16)(controls.size() - sizeof(quint16));
    QTcpSocket * serwer = &madNet.socket;
    serwer->write(controls.data(), controls.size());

}

void MadViewer::keyPressEvent(QKeyEvent* event)
{
    if(!isConnected) {
        QWidget::keyPressEvent(event);
        return;
    }
    qDebug() << "key: " << event->text();
    sendControls(event->key());

}

void MadViewer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug("Pressed at: (%d x %d)", event->pos().x(), event->pos().y());
        pressed = true;
    }
}

void MadViewer::wheelEvent(QWheelEvent *event)
{
    qDebug("SCROLL: %d", event->delta());
}

void MadViewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && pressed) {
        qDebug("Released at: (%d x %d)", event->pos().x(), event->pos().y());
        pressed = false;
    }
}

void MadViewer::mouseMoveEvent(QMouseEvent *event)
{
       qDebug("Moving at: (%d x %d)", event->x(), event->y());
       sendControls(event->x());

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
    eventType   1
    eventData1  kierunek (1 - gora, 2 - dol)
    eventData2  ilosc (zwykle jest 120 na jeden skok kolka)

klawiatura:
    eventType   1
    eventData1  kod klawisza (event->key)
    eventData2  1 - wcisniecie 2- zwolnienie
*/
