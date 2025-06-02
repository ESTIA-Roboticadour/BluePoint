#pragma once

#include "MainWindow.h"
#include "DeviceView.h"
#include "ConfigurationView.h"

#include "CallbackTypes.h"
#include "Config.h"
#include "CameraConfig.h"
#include "LightControlConfig.h"

#include <QString>

class ViewFactory
{
public:
	static MainWindow* createMainWindow();
	static DeviceView* createDeviceView(const QString& cameraType, CameraConfig* cameraConfig, LightControlConfig* lightConfig, QWidget* parent=nullptr);
	static ConfigurationView* createConfigurationView(const QString& title, Config* config, QWidget* parent = nullptr, const ConfigValidatorCallback& validator = {});
	static ConfigurationView* createConfigurationView(const QString& title, Config* config, bool isReadOnly, QWidget* parent = nullptr, const ConfigValidatorCallback& validator = {});
};
