#include "AppStore.h"

bool AppStore::s_initialized = false;
bool AppStore::s_isInEdition = false;

QSettings* AppStore::s_settings = nullptr;

AppConfig* AppStore::s_appConfig = nullptr;
LightControlConfig* AppStore::s_lightControlConfig = nullptr;
CameraConfig* AppStore::s_cameraConfig = nullptr;
RoiConfig* AppStore::s_roiConfig = nullptr;

void AppStore::setSettings(QSettings* settings)
{
	if (!s_settings)
		s_settings = settings;
}

void AppStore::setAppConfigPath(const QString& path)
{
	if (s_settings)
	{
		s_settings->setValue("General/AppConfigPath", path);
	}
}

QString AppStore::getAppConfigPath()
{
	return s_settings ?
		s_settings->value("General/AppConfigPath", DEFAULT_FILE_PATH).toString() :
		getDefaultAppConfigPath();
}

QString AppStore::getDefaultAppConfigPath()
{
	return DEFAULT_FILE_PATH;
}

QSettings* AppStore::getSettings()
{
	return s_settings;
}

void AppStore::setIsInEdition(bool isInEdition) { s_isInEdition = isInEdition; }
bool AppStore::isInEdition() { return s_isInEdition; }

void AppStore::init(
	AppConfig* appConfig, 
	LightControlConfig* lightControlConfig,
	CameraConfig* cameraConfig, 
	RoiConfig* roiConfig
	)
{
	if (!s_initialized)
	{
		s_appConfig = appConfig;
		s_lightControlConfig = lightControlConfig;
		s_cameraConfig = cameraConfig;
		s_roiConfig = roiConfig;

		s_initialized = true;
	}
}

void AppStore::deleteAll()
{
	deleteObject(s_appConfig);
	deleteObject(s_lightControlConfig);
	deleteObject(s_cameraConfig);
	deleteObject(s_roiConfig);
	deleteObject(s_settings);
}

void AppStore::deleteObject(QObject* o)
{
	if (o)
	{
		o->deleteLater();
		o = nullptr;
	}
}

AppConfig* AppStore::getAppConfig()
{
	return s_appConfig;
}

LightControlConfig* AppStore::getLightControlConfig()
{
	return s_lightControlConfig;
}

CameraConfig* AppStore::getCameraConfig()
{
	return s_cameraConfig;
}

RoiConfig* AppStore::getRoiConfig()
{
	return s_roiConfig;
}
