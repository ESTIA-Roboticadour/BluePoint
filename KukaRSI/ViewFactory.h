#pragma once
#include "MainWindow.h"
#include "CallbackTypes.h"
#include "Config.h"
#include "RobotConfig.h"
#include "RobotKuka.h"
#include "ConfigurationView.h"
#include "AppView.h"

class ViewFactory
{
public:
	static MainWindow* createMainWindow();
	static ConfigurationView* createConfigurationView(const QString& title, Config* config, QWidget* parent = nullptr, const ConfigValidatorCallback& validator = {});
	static ConfigurationView* createConfigurationView(const QString& title, Config* config, bool isReadOnly, QWidget* parent = nullptr, const ConfigValidatorCallback& validator = {});
	static AppView* createAppView(RobotKuka* robot, const RobotConfig* config, QWidget* parent=nullptr);
};
