#include "CameraConfig.h"

CameraConfig::CameraConfig(QObject* parent) :
	Config(parent),
	m_width("Width", 640, this),
	m_height("Height", 480, this),
	m_fps("FPS", 30, this)
{
	defineBounds();
	addParameters();
}

CameraConfig::CameraConfig(int width, int height, int fps, QObject* parent) :
	Config(parent),
	m_width("Width", width, this),
	m_height("Height", height, this),
	m_fps("FPS", fps, this)
{
	defineBounds();
	addParameters();
}

CameraConfig::CameraConfig(const CameraConfig& config, QObject* parent) :
	Config(parent),
	m_width("Width", config.m_width, this),
	m_height("Height", config.m_height, this),
	m_fps("FPS", config.m_fps, this)
{
	defineBounds();
	addParameters();
}

int CameraConfig::getWidth() const
{
	return m_width.getValue();
}

int CameraConfig::getHeight() const
{
	return m_height.getValue();
}

int CameraConfig::getFps() const
{
	return m_fps.getValue();
}

void CameraConfig::setWidth(const int width)
{
	m_width.setValue(width);
}

void CameraConfig::setHeight(const int height)
{
	m_height.setValue(height);
}

void CameraConfig::setFps(const int fps)
{
	m_fps.setValue(fps);
}

void CameraConfig::defineBounds()
{
	m_width.setMinimum(1);
	m_width.setMaximum(8192);

	m_height.setMinimum(1);
	m_height.setMaximum(8192);

	m_fps.setMinimum(1);
	m_fps.setMaximum(120);
}

void CameraConfig::addParameters()
{
	addParameter(&m_width);
	addParameter(&m_height);
	addParameter(&m_fps);
}
