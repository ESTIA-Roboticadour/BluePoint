#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include "ViewFactory.h"

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);
    CameraHeightWindow* w = ViewFactory::createCameraHeightWindow();
    w->show();
    return a.exec();
}
