#ifndef MADVIEWER_H_
#define MADVIEWER_H_

#include <QtGui>
#include <QtNetwork>
#include "MadNet.h"

class MadViewer: public QDialog {

    Q_OBJECT

public:
    QLineEdit *addressEdit;

    static const qint16 ALL_PIC=1000000;
    MadViewer(QWidget *parent = 0);

    void MadViewer::mousePressEvent(QMouseEvent *event);
    void MadViewer::mouseReleaseEvent(QMouseEvent *event);
    void MadViewer::mouseMoveEvent(QMouseEvent *event);
    void MadViewer::wheelEvent(QWheelEvent *event);
    void MadViewer::keyPressEvent(QKeyEvent * event);

public slots:
    void connectedToServer();
    void disconnectedFromServer();

    void drawImage();
    void manageClicked();
    void enableConnectButton();

private:
    MadNet madNet;
    QPushButton *connectButton, *exitButton;
    QLabel *addressLabel, *mainViewLabel;
    QImage img;

    quint64 nextBlock;
    bool pressed;
    bool isConnected;
};

#endif /* MADVIEWER_H_ */
