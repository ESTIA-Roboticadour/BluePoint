#pragma once

#include "MainWindow.h"
#include "DeviceView.h"

#include "CameraConfig.h"
#include "LightControlConfig.h"
#include "Camera.h"

class ViewFactory
{
public:
	static MainWindow* createMainWindow();
	static DeviceView* createDeviceView(CameraConfig* cameraConfig, LightControlConfig* lightConfig, Camera* camera, QWidget* parentView=nullptr);
};
