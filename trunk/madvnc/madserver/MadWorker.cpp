/*
* MadPix.cpp
*
*  Created on: 2009-06-25
*      Author: dziq
*/

#include "MadWorker.h"
#include <QtGui>

MadWorker::MadWorker() {
	oldimg = new QImage();
	stoped=true;
}

void MadWorker::getImage(QImage &newer,QImage& older){

		quint16 lines2send;
		buffer= new QByteArray();
		QDataStream stream(buffer,QIODevice::WriteOnly);
		stream.setVersion(QDataStream::Qt_4_1);

		//qDebug() << "worker" << QThread::currentThread();
		if (!stoped) emit nextPlease();
		if (older.isNull()){
		//	if (true) {
			stream << quint64(0);
			stream << ALL_PIC;
			stream << newer;
			stream.device()->seek(0);
			stream << quint64(buffer->size() -sizeof(quint64));	
			emit sendBuffer(buffer);
		} else {
			uchar * oldptr,* imgptr;
			lines2send=0;
			stream<<quint64(0); //przyszla wielkosc bufora
			stream<<quint16(0); //przyszla ilosc lini do wyslania
			quint16 ilosc = newer.height()/PODZIAL;
			quint16 bpl = newer.bytesPerLine();
			QImage tempimg = QImage(1280,ilosc,QImage::Format_ARGB32);
			for (int i=0;i<PODZIAL;i++){
				oldptr=older.bits()+i*ilosc*bpl;
				imgptr=newer.bits()+i*ilosc*bpl;
				for (int j=0;j<bpl*ilosc;j++){
					if (oldptr[j]!=imgptr[j]){
					//if (true){
						stream << quint16(i);
						memcpy(tempimg.bits(),imgptr,bpl*ilosc);
						
						stream << tempimg;
						//qDebug() << tempimg.pixel(QPoint(0,0));
						lines2send++;
						break;
					}
				}

			}

			if (lines2send>0){
				stream.device()->seek(0);
				stream << quint64(buffer->size() -sizeof(quint64));	
				stream << quint16(lines2send);
				emit sendBuffer(buffer);
				
			} else {
				delete buffer;
			}
		}
}

void MadWorker::stopingWorking(){
	stoped=true;
}