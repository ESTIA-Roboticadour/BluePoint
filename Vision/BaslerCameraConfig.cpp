#include "BaslerCameraConfig.h"
#include "ListParameterBase.h"

BaslerCameraConfig::BaslerCameraConfig(QObject* parent) :
	CameraConfig(parent),
	m_maximumWidth("Maximum Width", 5048, this),
	m_maximumHeight("Maximum Height", 5048, this),
	m_offsetX("Offset X", 0, this),
	m_offsetY("Offset Y", 0, this),
	m_formats("Formats", this),
	m_exposureTime("Exposure Time", 33, this),
	m_gainDB("Gain DB", 0, this)
{
	m_width.setValue(2048);
	m_height.setValue(2048);
	m_fps.setValue(29.);
	m_formats.addItem("Bayer RG 8", "BayerRG8");

	defineBounds();
	addParameters();
	m_formats.setIsEditable(false); // Formats should not be editable by the user
	setupConnections();
}

BaslerCameraConfig::BaslerCameraConfig(const BaslerCameraConfig& config, QObject* parent) :
	CameraConfig(parent),
	m_maximumWidth("Maximum Width", config.m_maximumWidth, this),
	m_maximumHeight("Maximum Height", config.m_maximumHeight, this),
	m_offsetX("Offset X", config.m_offsetX, this),
	m_offsetY("Offset Y", config.m_offsetY, this),
	m_formats("Formats", this),
	m_exposureTime("Exposure Time", config.m_exposureTime, this),
	m_gainDB("Gain DB", config.m_gainDB, this)
{
	m_width.setValue(config.m_width.getValue());
	m_height.setValue(config.m_height.getValue());
	m_fps.setValue(config.m_fps.getValue());
	m_formats.addItem("Bayer RG 8", "BayerRG8");
	defineBounds();
	addParameters();
	m_formats.setIsEditable(false); // Formats should not be editable by the user
	setupConnections();
}

int BaslerCameraConfig::getMaximumWidth() const
{
	return m_maximumWidth.getValue();
}

int BaslerCameraConfig::getMaximumHeight() const
{
	return m_maximumHeight.getValue();
}

int BaslerCameraConfig::getOffsetX() const
{
	return m_offsetX.getValue();
}

int BaslerCameraConfig::getOffsetY() const
{
	return m_offsetY.getValue();
}

QString BaslerCameraConfig::getSelectedFormat() const
{
	return m_formats.getSelectedValue().toString();
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

void BaslerCameraConfig::setupConnections()
{
	connect(&m_maximumWidth, &NumericalParameter::valueChanged, this, &BaslerCameraConfig::setBoundsByMaximums);
	connect(&m_maximumHeight, &NumericalParameter::valueChanged, this, &BaslerCameraConfig::setBoundsByMaximums);
	connect(&m_offsetX, &NumericalParameter::valueChanged, this, &BaslerCameraConfig::boundWidthByMaxWidthAndOffsetX);
	connect(&m_offsetY, &NumericalParameter::valueChanged, this, &BaslerCameraConfig::boundHeightByMaxHeightAndOffsetY);
}

void BaslerCameraConfig::defineBounds()
{
	m_maximumWidth.setMinimum(2);
	m_maximumWidth.setMaximum(8192);
	m_maximumWidth.setIncrement(2);

	m_maximumHeight.setMinimum(2);
	m_maximumHeight.setMaximum(8192);
	m_maximumHeight.setIncrement(2);

	setBoundsByMaximums();

	m_exposureTime.setMinimum(1);
	m_exposureTime.setMaximum(1000);

	m_gainDB.setMaximum(48);
}

void BaslerCameraConfig::setBoundsByMaximums()
{
	m_offsetX.setMinimum(0);
	m_offsetX.setMaximum(m_maximumWidth.getValue());

	m_offsetY.setMinimum(0);
	m_offsetY.setMaximum(m_maximumHeight.getValue());

	m_width.setMaximum(m_maximumWidth.getValue());
	m_height.setMaximum(m_maximumHeight.getValue());

	boundWidthByMaxWidthAndOffsetX();
	boundHeightByMaxHeightAndOffsetY();
}

void BaslerCameraConfig::boundWidthByMaxWidthAndOffsetX()
{
	double maxWidth = m_maximumWidth.getValue() - m_offsetX.getValue();
	if (m_width.getValue() > maxWidth)
	{
		m_width.setValue(maxWidth);
	}
}

void BaslerCameraConfig::boundHeightByMaxHeightAndOffsetY()
{
	double maxHeight = m_maximumHeight.getValue() - m_offsetY.getValue();
	if (m_height.getValue() > maxHeight)
	{
		m_height.setValue(maxHeight);
	}
}

void BaslerCameraConfig::addParameters()
{
	addParameter(&m_maximumWidth);
	addParameter(&m_maximumHeight);
	addParameter(&m_offsetX);
	addParameter(&m_offsetY);
	addParameter(&m_formats);
	addParameter(&m_exposureTime);
	addParameter(&m_gainDB);
}

bool BaslerCameraConfig::setFromConfig(const Config* src, bool copyPath)
{
	Config::setFromConfig(src, copyPath);
	bool check1 = CameraConfig::setFromConfig(src, copyPath);

	int numberOfParametersToSet = 7;
	int numberOfParametersSet = 0;

	// Maximum Width
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Maximum Width")))
	{
		m_maximumWidth.setValue(param->getValue());
		numberOfParametersSet++;
	}

	// Maximum Height
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Maximum Height")))
	{
		m_maximumHeight.setValue(param->getValue());
		numberOfParametersSet++;
	}

	// Offset X
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Offset X")))
	{
		m_offsetX.setValue(param->getValue());
		numberOfParametersSet++;
	}

	// Offset Y
	if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Offset Y")))
	{
		m_offsetY.setValue(param->getValue());
		numberOfParametersSet++;
	}

	// Formats
	if (ListParameterBase* formatsList = qobject_cast<ListParameterBase*>(src->getParameter("Formats")))
	{
		m_formats.setIsEditable(true);
		m_formats.clear();
		for (const auto& item : formatsList->items())
		{
			m_formats.addItem(item.first, item.second.toString());
		}
		m_formats.selectValueByIndex(formatsList->getSelectedIndex());
		m_formats.setIsEditable(false); // Formats should not be editable by the user
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

	setBoundsByMaximums();

	return check1 && numberOfParametersToSet == numberOfParametersSet;
}
