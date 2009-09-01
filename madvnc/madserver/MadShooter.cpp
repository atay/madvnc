/*
* MadShooter.cpp
*
*  Created on: 2009-06-26
*      Author: dziq
*/

#include "MadShooter.h"
#include <QtGui>


MadShooter::MadShooter(){
	count=0;
	tempimg = QImage(WIDTH/PODZIAL,HEIGHT/PODZIAL,QImage::Format_RGB32);	
}
void MadShooter::run(){
	QThread::exec();
}
void MadShooter::showcount(){
	qDebug() << count/5;
	count=0;
}

void MadShooter::makeScreenShot(){


	img = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
	++count;



	quint16 partcount=0;
	buffer= new QByteArray();
	QDataStream stream(buffer,QIODevice::WriteOnly);
	stream.setVersion(QDataStream::Qt_4_1);

	if (oldimg.isNull()){

		stream << quint64(0);
		stream << MadShooter::ALL_PIC;
		stream << img;
		stream.device()->seek(0);
		stream << quint64(buffer->size()-sizeof(quint64));
		emit sendBuffer(buffer);
	} else {
		stream << quint64(0);
		stream << quint16(0);
		uchar * oldptr,* imgptr;
		bool send;

		for (int i=0;i<PODZIAL;i++){
			for (int j=0;j<PODZIAL;j++){
				send=false;
				imgptr=img.bits()+i*BPP*WIDTH*HEIGHT/PODZIAL+j*BPP*WIDTH/PODZIAL;
				oldptr=oldimg.bits()+i*BPP*WIDTH*HEIGHT/PODZIAL+j*BPP*WIDTH/PODZIAL;
				for (int k=0;k<(HEIGHT/PODZIAL);k++){
					for (int l=0;l<(WIDTH/PODZIAL);l++){
						if (imgptr[l+k*BPP*WIDTH]!=oldptr[l+k*BPP*WIDTH]){
							partcount++;
							stream << quint16(i);
							stream << quint16(j);
							for (int m=0;m<HEIGHT/PODZIAL;m++){
								memcpy(tempimg.scanLine(m),imgptr+m*BPP*WIDTH,BPP*WIDTH/PODZIAL);
							}
							stream << tempimg;
							send=true;
							break;

						}

						if (send) break;
					}
					if (send) break;
				}
						if (send){
			qDebug() << "wysylamy";
			stream.device()->seek(0);
			stream << quint64(sizeof(quint64));
			stream << quint16(partcount);
			emit sendBuffer(buffer);
		}
			}
		}


		qDebug() << "Koniec";
	}
	oldimg=img; //tutaj nie ma glebokiej kopii ??

}
