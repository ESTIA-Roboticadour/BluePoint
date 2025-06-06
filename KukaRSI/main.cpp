#include "ViewFactory.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ViewFactory::createMainWindow()->showMaximized();
    return app.exec();
}
