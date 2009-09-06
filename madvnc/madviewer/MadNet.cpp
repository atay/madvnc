#include "MadNet.h"

MadNet::MadNet(QObject * parent){

}

void MadNet::run(){
    exec();
}

void MadNet::connect(QString address){

    socket.connectToHost(address, 7777);
    qDebug("trying to connect..");
}

void MadNet::disconnect(){
    socket.disconnectFromHost();
    qDebug("disconnected");
}
