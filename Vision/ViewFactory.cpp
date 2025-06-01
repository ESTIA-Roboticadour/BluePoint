#include "ViewFactory.h"
#include "NavigationTree.h"

#include "MainModel.h"
#include "MainController.h"

#include "DeviceModel.h"
#include "DeviceController.h"

#include "ConfigurationModel.h"
#include "ConfigurationController.h"

MainWindow* ViewFactory::createMainWindow()
{
	MainWindow* mainWindow = new MainWindow();
	MainModel* model = new MainModel(mainWindow->getTree());
	MainController* controller = new MainController(model, mainWindow);
	return mainWindow;
}

DeviceView* ViewFactory::createDeviceView(const QString& cameraType, CameraConfig* cameraConfig, LightControlConfig* lightConfig, QWidget* parent)
{
	DeviceView* view = new DeviceView(parent);
	DeviceModel* model = new DeviceModel(cameraType, cameraConfig, lightConfig);
	DeviceController* controller = new DeviceController(model, view);
	return view;
}

ConfigurationView* ViewFactory::createConfigurationView(const QString& title, Config* config, QWidget* parent)
{
	ConfigurationModel* model = new ConfigurationModel(config);
	ConfigurationView* view = new ConfigurationView(title, parent);
	view->setConfig(model->getEditableConfig());
	ConfigurationController* controller = new ConfigurationController(model, view);
	return view;
}
