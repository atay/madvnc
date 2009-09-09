#include <QtGui>
#include <QtNetwork>
#include "MadViewer.h"
#include "MadLabel.h"

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

    mainViewLabel = new MadLabel(this);
    mainViewLabel->setMinimumSize(1280,800);
	//mainViewLabel->setFocusPolicy(Qt::StrongFocus);

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
	connect(mainViewLabel, SIGNAL(newMouseEvent(QMouseEvent*)),  &madNet, SLOT(sendMouseEvent(QMouseEvent*)));
	connect(mainViewLabel, SIGNAL(newKeyEvent(QKeyEvent*)),  &madNet, SLOT(sendKeyEvent(QKeyEvent*)));
	connect(mainViewLabel, SIGNAL(setStatus(const QString&)),  statusLabel, SLOT(setText(const QString &)));
	connect(this, SIGNAL(setStatus(const QString&)),  statusLabel, SLOT(setText(const QString &)));
	

    nextBlock = 0;
    img = QImage(1280,800,QImage::Format_RGB16);

}

void MadViewer::disconnectedFromServer(){
    mainViewLabel->setText("Connection finished..");
    connectButton->setText("Connect");
    isConnected = false;
    setMouseTracking(false);
	mainViewLabel->setMouseTracking(false);
	mainViewLabel->setFocusPolicy(Qt::StrongFocus);
	addressEdit->setDisabled(false);

}
void MadViewer::connectedToServer(){
    qDebug("connected");
    mainViewLabel->setText("Connection estabilished..");
    connectButton->setText("Disconnect");
    //connectButton->setEnabled(true);
    isConnected = true;
    setMouseTracking(true);
	mainViewLabel->setMouseTracking(true);
	connectButton->setDefault(false);
	connectButton->clearFocus();
	mainViewLabel->setFocus();
	addressEdit->setDisabled(true);
	this->setFocusProxy(mainViewLabel);

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

void MadViewer::keyPressEvent ( QKeyEvent * event){
	
}