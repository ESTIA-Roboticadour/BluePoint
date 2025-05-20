#include "ViewFactory.h"
#include "RoiTransformer.h"
#include <QGuiApplication>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication a(argc, argv);

    auto* w = ViewFactory::createMainWindow();
    w->showMaximized();

    return a.exec();
}
