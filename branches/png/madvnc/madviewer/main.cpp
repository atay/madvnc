#include <QApplication>
#include "MadSocket.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MadSocket madsocket;
    qDebug("test");
    madsocket.show();

    return a.exec();

}
