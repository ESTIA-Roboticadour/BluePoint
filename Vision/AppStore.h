#pragma once
#include "AppConfig.h"
#include "RoiConfig.h"
#include "LightControlConfig.h"
#include "CameraConfig.h"
#include "Camera.h"

#include <QObject>

class AppStore
{
public:
	void init(
		AppConfig* appConfig,
		LightControlConfig* lightControlConfig,
		CameraConfig* cameraConfig,
		RoiConfig* roiConfig,
		Camera* camera
	);

	static void deleteAll();

	static void setEditionMode(bool isInEdition);
	static bool isInEdition();
	
	static AppConfig* getAppConfig();
	static LightControlConfig* getLightControlConfig();
	static CameraConfig* getCameraConfig();
	static RoiConfig* getRoiConfig();
	static Camera* getCamera();

private:
	static void deleteObject(QObject* o);

private:
	static bool s_initialized;
	static bool s_isInEdition;

	static AppConfig* s_appConfig;
	static LightControlConfig* s_lightControlConfig;
	static CameraConfig* s_cameraConfig;
	static RoiConfig* s_roiConfig;
	static Camera* s_camera;
};

