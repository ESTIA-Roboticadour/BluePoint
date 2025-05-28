#include "CameraFactory.h"
#include "BaslerCameraConfig.h"
#include "BaslerCamera.h"

Camera* CameraFactory::createCamera(const QString& cameraType, CameraConfig* cameraConfig, QObject* parent)
{
	Camera* camera = nullptr;
	if (cameraType == "Basler")
	{
		if (BaslerCameraConfig* baslerConfig = qobject_cast<BaslerCameraConfig*>(cameraConfig))
		{
			camera = new BaslerCamera(parent);
			camera->setConfig(baslerConfig);
		}
		else
		{
			qCritical() << "Invalid camera configuration (" << cameraConfig->metaObject()->className()  << ") for Basler camera type";
		}
	}
	else
	{
		qWarning() << "Unsupported camera type:" << cameraType;
	}

	return camera;
}
