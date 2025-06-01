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

void BaslerCameraConfig::reset()
{
	BaslerCameraConfig newConfig;
	setFromConfig(&newConfig, false);
}

void BaslerCameraConfig::defineBounds()
{
	m_width.setMaximum(5048);
	m_height.setMaximum(5048);
}

void BaslerCameraConfig::addParameters()
{
}

bool BaslerCameraConfig::setFromConfig(const Config* src, bool copyPath)
{
	Config::setFromConfig(src, copyPath);
	return CameraConfig::setFromConfig(src, copyPath);
}
