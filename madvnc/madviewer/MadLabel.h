#ifndef MADLABEL_H
#define MADLABEL_H

#include <QLabel>


class MadLabel: public QLabel{

    Q_OBJECT

public:
    MadLabel(QWidget *parent =0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent ( QKeyEvent * event);
	void keyReleaseEvent ( QKeyEvent * event);
signals:
	void newMouseEvent(QMouseEvent*);
	void newKeyEvent(QKeyEvent*);
	void setStatus(const QString &);
};

#endif // MADLABEL_H
