#include "ViewFactory.h"
#include "AppStore.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ViewFactory::createMainWindow()->showMaximized();
    int status = app.exec();
    AppStore::deleteAll();
    return status;
}
