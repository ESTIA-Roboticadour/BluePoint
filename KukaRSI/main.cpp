#include "ViewFactory.h"
#include "AppStore.h"
#include "MovementDirection.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<MovementDirection>("MovementDirection");

    QApplication app(argc, argv);
    ViewFactory::createMainWindow()->showMaximized();
    int status = app.exec();
    AppStore::deleteAll();
    return status;
}
