#include "ViewFactory.h"
#include "NavigationTree.h"

MainWindow* ViewFactory::createMainWindow()
{
	MainWindow* mainWindow = new MainWindow();
	MainModel* model = new MainModel(mainWindow->getTree());
	MainController* controller = new MainController(model, mainWindow);
	return mainWindow;
}
