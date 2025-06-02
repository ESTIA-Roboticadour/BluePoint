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

ConfigurationView* ViewFactory::createConfigurationView(const QString& title, Config* config, QWidget* parent, const ConfigValidatorCallback& validator)
{
	return createConfigurationView(title, config, false, parent, validator);
}

ConfigurationView* ViewFactory::createConfigurationView(const QString& title, Config* config, bool isReadOnly, QWidget* parent, const ConfigValidatorCallback& validator)
{
	ConfigurationModel* model = new ConfigurationModel(config, nullptr, validator);
	ConfigurationView* view = new ConfigurationView(title, isReadOnly, parent);
	view->setConfig(model->getEditableConfig());
	ConfigurationController* controller = new ConfigurationController(model, view);
	return view;
}
