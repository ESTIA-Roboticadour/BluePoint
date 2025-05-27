#include "DeviceModel.h"

DeviceModel::DeviceModel(CameraConfig* cameraConfig, LightControlConfig* lightConfig, Camera* camera, QObject* parent) :
	ModelBase(parent),
	m_cameraConfig(cameraConfig),
	m_lightConfig(lightConfig),
	m_camera(camera)
{
}

void DeviceModel::release()
{
	if (m_camera && m_camera->isOpened()) {

		connect(m_camera, &Camera::closed, this, &DeviceModel::onCameraClosed);
		m_camera->close();
	}
	else {
		ModelBase::release();
	}
}

void DeviceModel::onCameraClosed()
{
	disconnect(m_camera, &Camera::closed, this, &DeviceModel::onCameraClosed);
	ModelBase::release();
}
