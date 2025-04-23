#include "CameraHeightModel.h"
#include <QtMath>

CameraHeightModel::CameraHeightModel(QObject* parent) :
	QObject(parent),
	m_fov(0),
	m_width(0),
	m_height(0)
{
}

CameraHeightModel::CameraHeightModel(float fov, float width, QObject* parent) :
	QObject(parent),
	m_fov(fov),
	m_width(width),
	m_height(0)
{
	computeHeight();
}

void CameraHeightModel::setFov(float fov)
{
	if (m_fov != fov)
	{
		m_fov = fov;
		emit fovChanged(m_fov);
		computeHeight();
	}
}

void CameraHeightModel::setWidth(float width)
{
	if (m_width != width)
	{
		m_width = width;
		emit widthChanged(m_width);
		computeHeight();
	}
}

void CameraHeightModel::setHeight(float height)
{
	if (m_height != height)
	{
		m_height = height;
		emit heightChanged(height);
	}
}

float CameraHeightModel::getFov() const
{
	return m_fov;
}

float CameraHeightModel::getWidth() const
{
	return m_width;
}

float CameraHeightModel::getHeight() const
{
	return m_height;
}

void CameraHeightModel::computeHeight()
{
	if (m_fov == 0)
	{
		emit errorThrowed("Divide by 0", "FOV can not be equal to 0.");
	}
	else
	{
		setHeight(m_width / (2.f * qTan(qDegreesToRadians(m_fov) / 2.f)));
	}
}
