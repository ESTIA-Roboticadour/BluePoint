#include "CameraProcessor.h"
#include <cmath>

CameraProcessor::CameraProcessor(QObject* parent) :
	QObject(parent),
	m_height(0),
	m_width(0),
	m_fps(0.f),
	m_workWidth(0),
	m_workHeight(0)
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

int CameraProcessor::getWorkWidth() const
{
	return m_workWidth;
}

int CameraProcessor::getWorkHeight() const
{
	return m_workHeight;
}

QSize CameraProcessor::getWorkDimensions() const
{
	return QSize(m_workWidth, m_workHeight);
}

void CameraProcessor::setWorkWidth(int width)
{
	if (m_workWidth != width)
	{
		m_workWidth = width;
		emit workDimensionsChanged(m_workWidth, m_workHeight);
	}
}

void CameraProcessor::setWorkHeight(int height)
{
	if (m_workHeight != height)
	{
		m_workHeight = height;
		emit workDimensionsChanged(m_workWidth, m_workHeight);
	}
}

void CameraProcessor::setWorkDimensions(int width, int height)
{
	if (m_workWidth != width || m_workHeight != height)
	{
		m_workWidth = width;
		m_workHeight = height;
		emit workDimensionsChanged(m_workWidth, m_workHeight);
	}
}

void CameraProcessor::setWorkDimensions(const QSize& size)
{
	if (m_workWidth != size.width() || m_workHeight != size.height())
	{
		m_workWidth = size.width();
		m_workHeight = size.height();
		emit workDimensionsChanged(m_workWidth, m_workHeight);
	}
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

void CameraProcessor::findNewSizeToKeepAspectRatio(int originalWidth, int originalHeight, int& newWidth, int& newHeight) const
{
	if (m_workWidth == 0 || m_workHeight == 0 || m_workWidth == originalWidth || m_workHeight == originalHeight)
	{
		newWidth = originalWidth;
		newHeight = originalHeight;
	}
	else
	{
		float ratioWidth =  (float)originalWidth / (float)m_workWidth;
		float ratioHeight = (float)originalHeight / (float)m_workHeight;

		if (ratioWidth > ratioHeight)
		{
			// Width is the dominant dimension
			newWidth = m_workWidth;
			newHeight = (int)std::roundf((float)originalHeight / ratioWidth);
		}
		else
		{
			// Height is the dominant dimension
			newHeight = m_workHeight;
			newWidth = (int)std::roundf((float)originalWidth / ratioHeight);
		}
	}
}
