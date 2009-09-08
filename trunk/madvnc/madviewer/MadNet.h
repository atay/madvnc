#ifndef MADNET_H
#define MADNET_H

#include <QTcpSocket>
#include <QThread>
#include <QtGui>

//class QThread;

class MadNet: public QThread{

    Q_OBJECT

public:
    MadNet(QObject *parent =0);
    QTcpSocket socket;

private:

protected:
    void run();

public slots:
    void connect(QString);
    void disconnect();
	void sendMouseEvent(QMouseEvent);
	void sendKeyEvent(QKeyEvent);
	void sendWheelEvent(QWheelEvent);

};

#endif // MADNET_H
