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
	if (event->button()==Qt::LeftButton) emit setStatus("Wci�ni�to LPM");
	else if (event->button()==Qt::RightButton) emit setStatus("Wci�ni�to PPM");
	emit newMouseEvent(event);
}

void MadLabel::mouseReleaseEvent(QMouseEvent *event)
{
	emit newMouseEvent(event);
}
void MadLabel::keyPressEvent ( QKeyEvent * event){
	emit setStatus("Wcisni�to klawisz: " + QString(event->modifiers() & Qt::ControlModifier ? "CTRL + " : "") 
		+ QString(event->modifiers() & Qt::ShiftModifier ? "SHIFT + " : "") 
		+ QString(event->modifiers() & Qt::AltModifier ? "ALT + " : "") + QString(event->key()));
	
	emit newKeyEvent(event);
}
void MadLabel::keyReleaseEvent ( QKeyEvent * event){
	emit newKeyEvent(event);
}