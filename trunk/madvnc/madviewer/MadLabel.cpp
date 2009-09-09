#include "MadLabel.h"
#include <QtGui>

MadLabel::MadLabel(QWidget *parent) : QLabel(parent){


}

void MadLabel::mouseMoveEvent(QMouseEvent *event) {
	emit newMouseEvent(event);
	emit setStatus("Pozycja myszy ( x: " + QString::number(event->pos().x()) + " , y: " + QString::number(event->pos().y()) + " )");
}

void MadLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button()==Qt::LeftButton) emit setStatus("Wciœniêto LPM");
	else if (event->button()==Qt::RightButton) emit setStatus("Wciœniêto PPM");
	emit newMouseEvent(event);
}

void MadLabel::mouseReleaseEvent(QMouseEvent *event)
{
	emit newMouseEvent(event);
}
void MadLabel::keyPressEvent ( QKeyEvent * event){
	emit setStatus("Wcisniêto klawisz: " + QString(event->modifiers() & Qt::ControlModifier ? "CTRL + " : "") 
		+ QString(event->modifiers() & Qt::ShiftModifier ? "SHIFT + " : "") 
		+ QString(event->modifiers() & Qt::AltModifier ? "ALT + " : "") + QString(event->key()));
	
	emit newKeyEvent(event);
}
void MadLabel::keyReleaseEvent ( QKeyEvent * event){
	emit newKeyEvent(event);
}