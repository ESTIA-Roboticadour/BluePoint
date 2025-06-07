#include "ViewFactory.h"

#include "MainModel.h"
#include "MainController.h"

#include "ConfigurationModel.h"
#include "ConfigurationController.h"

#include "AppModel.h"
#include "AppController.h"

MainWindow* ViewFactory::createMainWindow()
{
	MainWindow* mainWindow = new MainWindow();
	MainModel* model = new MainModel(mainWindow->getTree());
	MainController* controller = new MainController(model, mainWindow);
	return mainWindow;
}

ConfigurationView* ViewFactory::createConfigurationView(const QString& title, Config* config, QWidget* parent, const ConfigValidatorCallback& validator)
{
	return createConfigurationView(title, config, false, parent, validator);
}

ConfigurationView* ViewFactory::createConfigurationView(const QString& title, Config* config, bool isReadOnly, QWidget* parent, const ConfigValidatorCallback& validator)
{
	ConfigurationModel* model = new ConfigurationModel(config, nullptr, validator);
	ConfigurationView* view = new ConfigurationView(title, isReadOnly, parent);
	ConfigurationController* controller = new ConfigurationController(model, view);
	return view;
}

AppView* ViewFactory::createAppView(const RobotConfig* config, QWidget* parent)
{
	AppModel* model = new AppModel(config);
	AppView* view = new AppView(parent);
	AppController* controller = new AppController(model, view);
	return view;
}
