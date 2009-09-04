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
    addressLabel = new QLabel("MadServer &aadress :");
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

    connect(&madNet.socket, SIGNAL(readyRead()),     this, SLOT(drawImage()));
    connect(&madNet.socket, SIGNAL(connected()),     this, SLOT(connectedToServer()));
    connect(&madNet.socket, SIGNAL(disconnected()),  this, SLOT(disconnectedFromServer()));
    //connect(&madNet.socket, SIGNAL(error(SocketError &)),this, SLOT(connectionError(QAbstractSocket::SocketError socketError)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mainViewLabel);
    layout->addLayout(controls);
    setLayout(layout);

    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

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

    mainViewLabel->setPixmap(QPixmap::fromImage(img));
    nextBlock = 0;

}

void MadViewer::keyPressEvent(QKeyEvent* event)
{
    qDebug("key: %d", event->key());
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
    if (pressed)
        qDebug("Moving at: (%d x %d)", event->x(), event->y());
}
