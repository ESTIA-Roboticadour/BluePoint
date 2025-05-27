#include "ViewFactory.h"
#include "NavigationTree.h"

#include "MainModel.h"
#include "MainController.h"

#include "DeviceModel.h"
#include "DeviceController.h"

MainWindow* ViewFactory::createMainWindow()
{
	MainWindow* mainWindow = new MainWindow();
	MainModel* model = new MainModel(mainWindow->getTree());
	MainController* controller = new MainController(model, mainWindow);
	return mainWindow;
}

DeviceView* ViewFactory::createDeviceView(CameraConfig* cameraConfig, LightControlConfig* lightConfig, Camera* camera, QWidget* parentView)
{
	DeviceView* view = new DeviceView(parentView);
	DeviceModel* model = new DeviceModel(cameraConfig, lightConfig, camera);
	DeviceController* controller = new DeviceController(model, view);
	return view;
}
