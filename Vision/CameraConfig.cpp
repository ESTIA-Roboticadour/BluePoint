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

void CameraConfig::reset()
{
	CameraConfig newConfig;
	setFromConfig(&newConfig, false);
}

void CameraConfig::defineBounds()
{
	m_width.setMinimum(2);
	m_width.setMaximum(8192);
	m_width.setIncrement(2);

	m_height.setMinimum(2);
	m_height.setMaximum(8192);
	m_height.setIncrement(2);

	m_fps.setMinimum(1);
	m_fps.setMaximum(120);
	m_fps.setIncrement(1);
}

void CameraConfig::addParameters()
{
	addParameter(&m_width);
	addParameter(&m_height);
	addParameter(&m_fps);
}

bool CameraConfig::setFromConfig(const Config* src, bool copyPath)
{
	int numberOfParametersToSet = 3;
	int numberOfParametersSet = 0;

	Config::setFromConfig(src, copyPath);
	if (src)
	{
		if (NumericalParameter* width = qobject_cast<NumericalParameter*>(src->getParameter("Width")))
		{
			m_width.setValue(width->getValue());
			numberOfParametersSet++;
		}
		else
		{
			m_width.setValue(640); // Default value
		}

		if (NumericalParameter* height = qobject_cast<NumericalParameter*>(src->getParameter("Height")))
		{
			m_height.setValue(height->getValue());
			numberOfParametersSet++;
		}
		else
		{
			m_height.setValue(480); // Default value
		}

		if (NumericalParameter* fps = qobject_cast<NumericalParameter*>(src->getParameter("FPS")))
		{
			m_fps.setValue(fps->getValue());
			numberOfParametersSet++;
		}
		else
		{
			m_fps.setValue(30); // Default value
		}
	}
	return numberOfParametersSet == numberOfParametersToSet;
}