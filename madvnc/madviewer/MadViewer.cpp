#include <QtGui>
#include <QtNetwork>
//#include <QTest>
#include "MadViewer.h"

MadViewer::MadViewer(QWidget * parent) : QDialog(parent) {

    connectButton = new QPushButton(tr("Connect"));
    connectButton->setEnabled(true);
    connectButton->setDefault(true);

    exitButton = new QPushButton(tr("Exit"));
    exitButton->setEnabled(true);

    addressEdit = new QLineEdit("1.1.1.1");
    addressLabel = new QLabel(tr("&Adres MadServer'a:"));
    addressLabel->setBuddy(addressEdit);

    QHBoxLayout *controls = new QHBoxLayout;

    controls->addWidget(addressLabel);
    controls->addWidget(addressEdit);
    controls->addWidget(connectButton);
    controls->addWidget(exitButton);

    connect(addressEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableConnectButton()));
    connect(connectButton, SIGNAL(clicked()), this, SLOT(manageConnection()));
    connect(exitButton, SIGNAL(clicked()), this , SLOT(close() ) );

    mainViewLabel = new QLabel(tr("Welcome in MADVNC program.."));
    mainViewLabel->setMinimumSize(800,600);
    //mainViewLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(&socket,    SIGNAL(readyRead()),    this,   SLOT(drawWindow()));
    connect(&socket,    SIGNAL(statechanged()), this,   SLOT(manageConnection()));
    //connect(&socket,    SIGNAL(error()),        this,   SLOT(manageConnection()));
    //connect(&socket,    SIGNAL(disconected()),  this,   SLOT(manageConnection()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mainViewLabel);
    layout->addLayout(controls);
    setLayout(layout);

    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    nextBlock = 0;
    img = QImage(800,600,QImage::Format_RGB16);
}



void MadViewer::manageConnection() {

    if(socket.state()==0)   // disconnected
    {
        connectButton->setEnabled(false);
        addressEdit->setEnabled(false);
        socket.connectToHost(addressEdit->text(), 7777);
        mainViewLabel->setText("Connecting to " + addressEdit->text());
        if (socket.waitForConnected(1000))
        {
            mainViewLabel->setText("Connected!");
        }
        else
        {
            mainViewLabel->setText("Connection failed.. Check address and try again.");
        }
        connectButton->setEnabled(true);
    }
    else
        //        if(socket.state()== 3)
    {
        socket.close();
        mainViewLabel->setText("Connection closed by user..");
        connectButton->setText("Connect");
        addressEdit->setReadOnly(true);
    }
}

void MadViewer::enableConnectButton() {

    connectButton->setEnabled( !addressEdit->text().isEmpty() );
}

void MadViewer::drawWindow() {

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
