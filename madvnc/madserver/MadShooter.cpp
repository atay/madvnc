/*
 * MadShooter.cpp
 *
 *  Created on: 2009-06-26
 *      Author: dziq
 */

#include "MadShooter.h"
#include <QtGui>


MadShooter::MadShooter(){
}
void MadShooter::run(){
	QThread::exec();
}
void MadShooter::makeScreenShot(){


	img = QPixmap::grabWindow(QApplication::desktop()->winId()).scaled(
                        QSize(1280, 800), Qt::KeepAspectRatio, Qt::SmoothTransformation).toImage().convertToFormat(QImage::Format_RGB16,Qt::AvoidDither|Qt::ThresholdDither);
	
	quint16 lines2send;
	buffer= new QByteArray();
	QDataStream stream(buffer,QIODevice::WriteOnly);
	stream.setVersion(QDataStream::Qt_4_1);

	if (oldimg.isNull()){

		stream<<quint64(img.numBytes()-sizeof(quint64)-sizeof(quint16));
		stream << ALL_PIC;
		stream.writeBytes((const char *)img.bits(),img.numBytes());
		emit sendBuffer(buffer);
	} else {
		uchar * oldptr,* imgptr;
		lines2send=0;
		stream<<quint64(0);
		stream<<quint16(0);
		stream<<uint(img.bytesPerLine());

		for (int i=0;i<img.height();i++){
			oldptr=oldimg.scanLine(i);
			imgptr=img.scanLine(i);
			for (int j=0;j<img.bytesPerLine();j++){
				if (oldptr[j]!=imgptr[j]){
					stream << quint16(i);
					stream.writeBytes((const char *)imgptr,img.bytesPerLine());
					lines2send++;
					break;
				}
			}

		}

		if (lines2send>0){
			stream.device()->seek(0);
			stream << quint64(buffer->size() -sizeof(quint64)-sizeof(quint16)-sizeof(uint));	
			stream << quint16(lines2send);
			emit sendBuffer(buffer);
		}
	}
	oldimg=img; //tutaj nie ma glebokiej kopii ??

}

