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
}

void MadWorker::getImage(QImage &newer,QImage& older){

		quint16 lines2send;
		buffer= new QByteArray();
		QDataStream stream(buffer,QIODevice::WriteOnly);
		stream.setVersion(QDataStream::Qt_4_1);

		//qDebug() << "worker" << QThread::currentThread();
		emit nextPlease();
		if (older.isNull()){
			//if (true) {
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
			
			QImage tempimg = QImage(1024,1,QImage::Format_ARGB32);
			for (int i=0;i<newer.height();i++){
				oldptr=older.scanLine(i);
				imgptr=newer.scanLine(i);
				for (int j=0;j<newer.bytesPerLine();j++){
					if (oldptr[j]!=imgptr[j]){
						stream << quint16(i);
						memcpy(tempimg.bits(),imgptr,newer.bytesPerLine());
						
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
