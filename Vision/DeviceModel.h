#pragma once
#include "ModelBase.h"
#include "CameraConfig.h"
#include "LightControlConfig.h"
#include "Camera.h"

class DeviceModel : public ModelBase
{
	Q_OBJECT
public:
	explicit DeviceModel(CameraConfig* cameraConfig, LightControlConfig* lightConfig, Camera* camera, QObject* parent=nullptr);

	CameraConfig* getCameraConfig() const { return m_cameraConfig; }
	LightControlConfig* getLightConfig() const { return m_lightConfig; }
	Camera* getCamera() const { return m_camera; }

	void release() override;

private slots:
	void onCameraClosed();

private:
	CameraConfig* m_cameraConfig{ nullptr };
	LightControlConfig* m_lightConfig{ nullptr };
	Camera* m_camera{ nullptr };
};
