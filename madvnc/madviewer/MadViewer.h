#ifndef MADVIEWER_H_
#define MADVIEWER_H_

#include <QtGui>
#include <QtNetwork>

class MadViewer: public QDialog {

	Q_OBJECT

public:

	static const qint16 ALL_PIC=1000000;
	MadViewer(QWidget *parent = 0);
        void MadViewer::mousePressEvent(QMouseEvent *event);
        void MadViewer::mouseReleaseEvent(QMouseEvent *event);
        void MadViewer::mouseMoveEvent(QMouseEvent *event);
        void MadViewer::wheelEvent(QWheelEvent *event);
        void MadViewer::keyPressEvent(QKeyEvent * event);

public slots:

        void manageConnection();
	void enableConnectButton();
        void drawWindow();
	//void send();

private:
	QPushButton *connectButton, *sendButton, *exitButton;
	QLineEdit *addressEdit;
	QLabel *addressLabel, *mainViewLabel;
	QTcpSocket socket;
	quint64 nextBlock;
	QImage img;
        bool pressed;

};


#endif /* MADVIEWER_H_ */
