#include "ViewFactory.h"
#include "AppStore.h"
#include "LogDispatcher.h"
#include "Helper.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LogDispatcher::setUILogEnabled(false);
    LogDispatcher::setLogFile(Helper::makePathAbsolute("KukaRSI.log"));
    ViewFactory::createMainWindow()->showMaximized();
    int status = app.exec();
    AppStore::deleteAll();
    return status;
}
