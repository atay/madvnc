#ifndef MADVIEWER_H_
#define MADVIEWER_H_

#include <QtGui>
#include <QtNetwork>
#include "MadNet.h"

class MadViewer: public QDialog {

    Q_OBJECT


    QLineEdit *addressEdit;
    static const qint16 ALL_PIC=1000000;
	static const qint16 PODZIAL=16;

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

public:
    MadViewer(QWidget *parent = 0);
	QLabel *addressLabel, *mainViewLabel, *statusLabel;
signals:
	void newMouseEvent(QMouseEvent);
	void newKeyEvent(QKeyEvent);
	void newWheelEvent(QWheelEvent);

public slots:
    void manageClicked();
    void enableConnectButton();
    void connectedToServer();
    void disconnectedFromServer();

    void drawImage();
    void sendControls(quint16, quint16, quint16);

private:
    MadNet madNet;
    QPushButton *connectButton, *exitButton;
	
    QImage img;
    QByteArray *buffer;
    qint64 nextBlock;
    bool pressed;
    bool isConnected;
};

#endif /* MADVIEWER_H_ */
