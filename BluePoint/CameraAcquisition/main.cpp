#include "ViewFactory.h"
#include "OpenCvCameraReader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OpenCvCameraReader reader;
    CameraWindow* view = ViewFactory::createCameraWindow(&reader);

    view->show();
    return a.exec();
}
