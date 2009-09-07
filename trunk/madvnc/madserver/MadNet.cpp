/*
 * MadServer.cpp
 *
 *  Created on: 2009-06-25
 *      Author: dziq
 */
#include "MadNet.h"


MadNet::MadNet(){
    server.listen(QHostAddress::Any,7777);
    connect(&server,SIGNAL(newConnection()),this,SLOT(prepareClient()));

}

void MadNet::bytesWrite(qint64 size){

}
void MadNet::prepareClient() {
    client = server.nextPendingConnection();
    server.close();
    emit connectionStart();
    connect(client,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWrite(qint64)));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnectClient()));
    qDebug() << "connected";

    // do odbierania glupot od klienta
    connect(client, SIGNAL(readyRead()), this, SLOT(receiveControls()));

}

void MadNet::disconnectClient(){
    server.listen(QHostAddress::Any,7777);
    emit stopWorking();
}

void MadNet::sendBuffer(QByteArray *buffer) {


    int result=client->write(buffer->data(),buffer->size());
    //qDebug() << "net" << QThread::currentThread();
    //if (result==-1) emit error();
    //  emit sendDone();
    delete buffer;

}

void MadNet::receiveControls(){

    // wesola nowina - dane z myszy i klawiatury przychodza jak nalezy, ale tak
    // szybko ze ponizsze rozwiazanie nie jest wystarczajace - w strumieniu
    // zostaja sockecie client zostaja dane i wychodza z opoznieniem, sie wszystko
    // pierniczy, a client->bytesAvailable() rosnie coraz bardziej
    // milej zabawy

    QDataStream controls(client);
    controls.setVersion(QDataStream::Qt_4_1);
    qDebug("!!!!!BA > %d", client->bytesAvailable());
    quint16 m1, m2, m3;
    controls >> m1 >> m2 >> m3;
    qDebug() << ">>>>" << m1 << " >> " << m2 << " >> " << m3;
}
