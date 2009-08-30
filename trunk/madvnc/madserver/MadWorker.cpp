/*
* MadPix.cpp
*
*  Created on: 2009-06-25
*      Author: dziq
*/

#include "MadWorker.h"
#include <QtGui>

MadWorker::MadWorker() {
	
}


void MadWorker::run(){
	QThread::exec();
}
void MadWorker::getScreen(QImage img){


}
