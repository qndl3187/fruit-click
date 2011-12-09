#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtPlatrom w;
    w.show();

    return a.exec();
}
