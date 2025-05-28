#include "ViewFactory.h"
#include "AppSetup.h"
#include "AppStore.h"
#include "AppConfig.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    int status = -1;

    if (AppSetup::setupApp())
    {
        ViewFactory::createMainWindow()->showMaximized();
        AppSetup::shareMessages();

        status = app.exec();

        // Nettoyage de fin
        AppConfig::deleteBackupConfig();
    }
    else
    {
        AppSetup::showError();
    }
    AppStore::deleteAll();
    return status;
}
