#include <QApplication>

#include "echo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Echo *echo = new Echo;

    echo->show();
    return a.exec();
}
