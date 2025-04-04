#include "CameraReader.h"

CameraReader::CameraReader(int device, QObject* parent) :
	QObject(parent),
	m_height(0),
	m_width(0),
	m_fps(0),
	m_device(device)
{
}

int CameraReader::getWidth() const
{
	return m_width;
}

int CameraReader::getHeight() const
{
	return m_height;
}

int CameraReader::getFps() const
{
	return m_fps;
}

void CameraReader::setDevice(int device)
{
	if (m_device != device)
	{
		m_device = device;
		emit deviceChanged(device);
	}
}

int CameraReader::getDevice() const
{
	return m_device;
}

void CameraReader::setWidth(int width)
{
	if (m_width != width)
	{
		m_width = width;
		emit dimensionsChanged(m_width, m_height);
	}
}

void CameraReader::setHeight(int height)
{
	if (m_height != height)
	{
		m_height = height;
		emit dimensionsChanged(m_width, m_height);
	}
}

void CameraReader::setFps(int fps)
{
	if (m_fps != fps)
	{
		m_fps = fps;
		emit fpsChanged(m_fps);
	}
}
