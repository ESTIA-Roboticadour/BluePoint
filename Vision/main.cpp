#include "VisionWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VisionWindow w;
    w.show();
    return a.exec();
}
