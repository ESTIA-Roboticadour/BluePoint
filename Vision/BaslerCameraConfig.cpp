#include "BaslerCameraConfig.h"
#include "ListParameterBase.h"

BaslerCameraConfig::BaslerCameraConfig(QObject* parent) :
	CameraConfig(parent),
	m_formats("Formats", this),
	m_exposureTime("Exposure Time", 33, this),
	m_gainDB("Gain DB", 0, this)
{
	m_fps.setValue(29.);
	m_formats.addItem("Bayer RG 8", "Bayer RG 8");

	defineBounds();
	addParameters();
}

BaslerCameraConfig::BaslerCameraConfig(const BaslerCameraConfig& config, QObject* parent) :
	CameraConfig(parent),
	m_formats("Formats", this),
	m_exposureTime("Exposure Time", config.m_exposureTime, this),
	m_gainDB("Gain DB", config.m_gainDB, this)
{
	m_fps.setValue(29.);
	m_formats.addItem("Bayer RG 8", "Bayer RG 8");
	defineBounds();
	addParameters();
}

QString BaslerCameraConfig::getSelectedFormat() const
{
	return m_formats.getSelectedKey();
}

QStringList BaslerCameraConfig::getFormats() const
{
	QStringList formats;
	const QVariantList& values = m_formats.getValues();
	for (auto& value : values)
		formats.append(value.toString());

	return formats;
}

int BaslerCameraConfig::getExposureTime() const
{
	return m_exposureTime.getValue();
}

int BaslerCameraConfig::getGainDB() const
{
	return m_gainDB.getValue();
}

void BaslerCameraConfig::reset()
{
	BaslerCameraConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* BaslerCameraConfig::copy(QObject* parent)
{
	BaslerCameraConfig* newConfig = new BaslerCameraConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

void BaslerCameraConfig::defineBounds()
{
	m_width.setMaximum(5048);
	m_height.setMaximum(5048);
	m_exposureTime.setMinimum(1);
	m_exposureTime.setMaximum(1000);
	m_gainDB.setMinimum(0);
	m_gainDB.setMaximum(48);

}

void BaslerCameraConfig::addParameters()
{
	addParameter(&m_formats);
	addParameter(&m_exposureTime);
	addParameter(&m_gainDB);
}

bool BaslerCameraConfig::setFromConfig(const Config* src, bool copyPath)
{
	Config::setFromConfig(src, copyPath);
	bool check1 = CameraConfig::setFromConfig(src, copyPath);

	int numberOfParametersToSet = 3;
	int numberOfParametersSet = 0;

	// Formats
	if (ListParameterBase* formatsList = qobject_cast<ListParameterBase*>(src->getParameter("Formats")))
	{
		m_formats.clear();
		for (const auto& item : formatsList->items())
		{
			m_formats.addItem(item.first, item.second.toString());
		}
		m_formats.selectValueByIndex(formatsList->getSelectedIndex());
		numberOfParametersSet++;
	}

	// Exposure Time
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Exposure Time")))
	{
		m_exposureTime.setValue(param->getValue());
		numberOfParametersSet++;
	}

	// Gain DB
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Gain DB")))
	{
		m_gainDB.setValue(param->getValue());
		numberOfParametersSet++;
	}
	return check1 && numberOfParametersToSet == numberOfParametersSet;
}
