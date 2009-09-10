#include "MadNet.h"

MadNet::MadNet(QObject * parent){

}

void MadNet::run(){
	QObject::connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(manageError(QAbstractSocket::SocketError)));
}

void MadNet::connect(QString address){

    socket.connectToHost(address, 7777);
    qDebug("Trying to connect..");
}

void MadNet::disconnect(){
    socket.disconnectFromHost();
    qDebug("Disconnected..");
}

void MadNet::sendMouseEvent(QMouseEvent *myEvent){
	QByteArray controls;
    QDataStream controlStream(&controls, QIODevice::ReadWrite);
    controlStream.setVersion(QDataStream::Qt_4_1);

    controlStream << quint16(0);
	controlStream	<< quint64(myEvent->type())
					<< myEvent->pos()
					<< quint64(myEvent->button())
					<< quint64(myEvent->buttons())
					<< quint64(myEvent->modifiers());
	
	
	
	
	controlStream.device()->seek(0);
	controlStream << quint16(controls.size() - sizeof(quint16));	

	socket.write(controls);
}


void MadNet::sendKeyEvent(QKeyEvent * myEvent){
	QByteArray controls;
    QDataStream controlStream(&controls, QIODevice::ReadWrite);
    controlStream.setVersion(QDataStream::Qt_4_1);

    controlStream << quint16(0);
	controlStream	<< quint64(myEvent->type())
					<< quint64(myEvent->key())
					<< quint64(myEvent->modifiers());
	
	controlStream.device()->seek(0);
	controlStream << quint16(controls.size() - sizeof(quint16));	

	socket.write(controls);
}
void MadNet::manageError(QAbstractSocket::SocketError error){
	emit emitError("Unable to connect (" + QString::number(error) + ")");
}