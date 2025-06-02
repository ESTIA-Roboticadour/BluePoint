#pragma once
#include "AppConfig.h"
#include "RoiConfig.h"
#include "LightControlConfig.h"
#include "CameraConfig.h"

#include <QObject>
#include <QSettings>

class AppStore
{
public:
	static void init(
		AppConfig* appConfig,
		LightControlConfig* lightControlConfig,
		CameraConfig* cameraConfig,
		RoiConfig* roiConfig
	);

	static void deleteAll();
	
	static void setSettings(QSettings* settings);
	static QSettings* getSettings();

	static void setAppConfigPath(const QString& path);
	static QString getAppConfigPath();
	static QString getDefaultAppConfigPath();

	static void setIsInEdition(bool isInEdition);
	static bool isInEdition();

	static AppConfig* getAppConfig();
	static LightControlConfig* getLightControlConfig();
	static CameraConfig* getCameraConfig();
	static RoiConfig* getRoiConfig();

	static void setLightControlConfig(LightControlConfig* lightConfig);
	static void setCameraConfig(CameraConfig* cameraConfig);
	static void setRoiConfig(RoiConfig* roiConfig);

	static void eraseCameraConfig();

private:
	static inline void deleteObject(QObject* o);

private:
	static const inline QString DEFAULT_FILE_PATH = "Config/App/default.json";

	static bool s_initialized;
	static bool s_isInEdition;

	static QSettings* s_settings;

	static AppConfig* s_appConfig;
	static LightControlConfig* s_lightControlConfig;
	static CameraConfig* s_cameraConfig;
	static RoiConfig* s_roiConfig;
};
