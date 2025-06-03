#include "RealSenseCameraConfig.h"

RealSenseCameraConfig::RealSenseCameraConfig(QObject* parent) :
	CameraConfig(parent),
	m_test("Test", 0, this)
{
	defineBounds();
	addParameters();
}

RealSenseCameraConfig::RealSenseCameraConfig(const RealSenseCameraConfig& config, QObject* parent) :
	CameraConfig(parent),
	m_test("Test", config.m_test, this)
{
	defineBounds();
	addParameters();
}


void RealSenseCameraConfig::reset()
{
	RealSenseCameraConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* RealSenseCameraConfig::copy(QObject* parent)
{
	RealSenseCameraConfig* newConfig = new RealSenseCameraConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

void RealSenseCameraConfig::defineBounds()
{
	m_width.setMaximum(5048);
	m_height.setMaximum(5048);
}

void RealSenseCameraConfig::addParameters()
{
	addParameter(&m_test);
}

bool RealSenseCameraConfig::setFromConfig(const Config* src, bool copyPath)
{
	Config::setFromConfig(src, copyPath);
	bool check1 = CameraConfig::setFromConfig(src, copyPath);

	int numberOfParametersToSet = 1;
	int numberOfParametersSet = 0;

	// Camera type
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Test")))
	{
		m_test.setValue(param->getValue());
		numberOfParametersSet++;
	}
	return check1 && numberOfParametersToSet == numberOfParametersSet;
}
