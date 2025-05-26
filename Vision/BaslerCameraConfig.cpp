#include "BaslerCameraConfig.h"

BaslerCameraConfig::BaslerCameraConfig(QObject* parent) :
	CameraConfig(parent)
{
	defineBounds();
	addParameters();
}

BaslerCameraConfig::BaslerCameraConfig(const BaslerCameraConfig& config, QObject* parent) :
	CameraConfig(parent)
{
	defineBounds();
	addParameters();
}

void BaslerCameraConfig::defineBounds()
{
	m_width.setMaximum(5048);
	m_height.setMaximum(5048);
}

void BaslerCameraConfig::addParameters()
{
}
