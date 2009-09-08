#include "MadNet.h"

MadNet::MadNet(QObject * parent){

}

void MadNet::run(){
    exec();
}

void MadNet::connect(QString address){

    socket.connectToHost(address, 7777);
    qDebug("Trying to connect..");
}

void MadNet::disconnect(){
    socket.disconnectFromHost();
    qDebug("Disconnected..");
}

void MadNet::sendMouseEvent(QMouseEvent myEvent){
	QByteArray controls;
    QDataStream controlStream(&controls, QIODevice::ReadWrite);
    controlStream.setVersion(QDataStream::Qt_4_1);

    controlStream << quint16(0);
	/*controlStream	<< quint64(myEvent.type())
					<< quint64(myEvent.pos().x())
					<< quint64(myEvent.pos().y())
					<< quint64(myEvent.button())
					<< quint64(myEvent.buttons())
					<< quint64(myEvent.modifiers());
	*/
	controlStream << quint16(100) <<quint16(myEvent.pos().x()) << quint16(200) << quint16(myEvent.pos().y()) << quint16(300) ;
	controlStream.device()->seek(0);
	controlStream << quint16(controls.size() - sizeof(quint16));	

	socket.write(controls);
}
void MadNet::sendKeyEvent(QKeyEvent myEvent){
	QByteArray controls;
    QDataStream controlStream(&controls, QIODevice::ReadWrite);
    controlStream.setVersion(QDataStream::Qt_4_1);

    controlStream << quint16(0);
	controlStream	<< quint64(myEvent.type())
					<< myEvent.key()
					<< (quint64)myEvent.modifiers();
	
	controlStream.device()->seek(0);
	controlStream << quint16(controls.size() - sizeof(quint16));	
	//this->statusLabel->setText(QString("mouse move: x: "+QString::number(myEvent->pos().x())+", y: "+QString::number(myEvent->pos().y())));
	//socket.write(controls);
}
void MadNet::sendWheelEvent(QWheelEvent myEvent){
}