#include "AppStore.h"

bool AppStore::s_initialized = false;
bool AppStore::s_isInEdition = false;

AppConfig* AppStore::s_appConfig = nullptr;
LightControlConfig* AppStore::s_lightControlConfig = nullptr;
CameraConfig* AppStore::s_cameraConfig = nullptr;
RoiConfig* AppStore::s_roiConfig = nullptr;
Camera* AppStore::s_camera = nullptr;

void AppStore::init(
	AppConfig* appConfig, 
	LightControlConfig* lightControlConfig,
	CameraConfig* cameraConfig, 
	RoiConfig* roiConfig, 
	Camera* camera)
{
	if (!s_initialized)
	{
		s_appConfig = appConfig;
		s_lightControlConfig = lightControlConfig;
		s_cameraConfig = cameraConfig;
		s_roiConfig = roiConfig;
		s_camera = camera;

		s_initialized = true;
	}
}

void AppStore::deleteAll()
{
	deleteObject(s_appConfig);
	deleteObject(s_lightControlConfig);
	deleteObject(s_cameraConfig);
	deleteObject(s_roiConfig);
	deleteObject(s_camera);
}

void AppStore::deleteObject(QObject* o)
{
	if (o)
	{
		o->deleteLater();
		o = nullptr;
	}
}

void AppStore::setEditionMode(bool isInEdition)
{
	s_isInEdition = isInEdition;
}

bool AppStore::isInEdition()
{
	return s_isInEdition;
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

Camera* AppStore::getCamera()
{
	return s_camera;
}
