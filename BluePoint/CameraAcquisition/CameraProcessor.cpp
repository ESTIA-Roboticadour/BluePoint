#include "CameraProcessor.h"

CameraProcessor::CameraProcessor(QObject* parent) :
	QObject(parent),
	m_height(0),
	m_width(0),
	m_fps(0.f)
{
}

int CameraProcessor::getWidth() const
{
	return m_width;
}

int CameraProcessor::getHeight() const
{
	return m_height;
}

float CameraProcessor::getFps() const
{
	return m_fps;
}

void CameraProcessor::setWidth(int width)
{
	if (m_width != width)
	{
		m_width = width;
		emit dimensionsChanged(m_width, m_height);
	}
}

void CameraProcessor::setHeight(int height)
{
	if (m_height != height)
	{
		m_height = height;
		emit dimensionsChanged(m_width, m_height);
	}
}

void CameraProcessor::setFps(float fps)
{
	if (m_fps != fps)
	{
		m_fps = fps;
		emit fpsChanged(m_fps);
	}
}
