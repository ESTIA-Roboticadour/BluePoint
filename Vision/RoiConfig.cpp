#include "RoiConfig.h"

RoiConfig::RoiConfig(QObject* parent) :
	Config(parent),
	m_x(NumericalParameter("X", 0, this)),
	m_y(NumericalParameter("Y", 0, this)),
	m_width(NumericalParameter("Width", 640, this)),
	m_height(NumericalParameter("Height", 640, this))
{
	defineBounds();
	addParameters();
}

RoiConfig::RoiConfig(int x, int y, int w, int h, QObject* parent) :
	Config(parent),
	m_x(NumericalParameter("X", 0, this)),
	m_y(NumericalParameter("Y", 0, this)),
	m_width(NumericalParameter("Width", 640, this)),
	m_height(NumericalParameter("Height", 640, this))
{
	defineBounds();
	setRoi(x, y, w, h);
	addParameters();
}

RoiConfig::RoiConfig(const RoiConfig& config, QObject* parent) :
	Config(parent),
	m_x("X", config.m_x),
	m_y("Y", config.m_y),
	m_width("Width", config.m_width),
	m_height("Height", config.m_height)
{
	defineBounds();
	addParameters();
}

void RoiConfig::defineBounds()
{
	m_x.setMinimum(0);
	m_x.setMinimum(8192);

	m_y.setMinimum(0);
	m_y.setMinimum(8192);

	m_width.setMinimum(1);
	m_width.setMaximum(8192);

	m_height.setMinimum(1);
	m_height.setMaximum(8192);
}

void RoiConfig::addParameters()
{
	addParameter(&m_x);
	addParameter(&m_y);
	addParameter(&m_width);
	addParameter(&m_height);
}

int RoiConfig::getX() const { return m_x.getValue(); }
int RoiConfig::getY() const { return m_y.getValue(); }
int RoiConfig::getWidth() const { return m_width.getValue(); }
int RoiConfig::getHeight() const { return m_height.getValue(); }
QPoint RoiConfig::getPos() const { return QPoint(m_x.getValue(), m_y.getValue()); }
QSize RoiConfig::getSize() const { return QSize(m_width.getValue(), m_height.getValue()); }
QRect RoiConfig::getRoi() const { return QRect(m_x.getValue(), m_y.getValue(), m_width.getValue(), m_height.getValue()); }

void RoiConfig::setX(const int x) 
{
	m_x.setValue(x);
}

void RoiConfig::setY(const int y) 
{
	m_y.setValue(y);
}

void RoiConfig::setWidth(const int w) 
{
	m_width.setValue(w);
}

void RoiConfig::setHeight(const int h) 
{
	m_height.setValue(h);
}

void RoiConfig::setPos(const int x, const int y) 
{
	m_x.setValue(x);
	m_y.setValue(y);
}

void RoiConfig::setPos(const QPoint& pos) 
{
	m_x.setValue(pos.x());
	m_y.setValue(pos.y());
}

void RoiConfig::setSize(const int w, const int h) 
{
	m_width.setValue(w);
	m_height.setValue(h);
}

void RoiConfig::setSize(const QSize& size) 
{
	m_width.setValue(size.width());
	m_height.setValue(size.height());
}

void RoiConfig::setRoi(const QRect& roi)
{
	setRoi(roi.x(), roi.y(), roi.width(), roi.height());
}

void RoiConfig::setRoi(const int x, const int y, const int width, const int height)
{
	m_x.setValue(x);
	m_y.setValue(y);
	m_width.setValue(width);
	m_height.setValue(height);
}

void RoiConfig::reset()
{
	RoiConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* RoiConfig::copy(QObject* parent) const
{
	RoiConfig* newConfig = new RoiConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

bool RoiConfig::setFromConfig(const Config* src, bool copyPath)
{
	int numberOfParametersToSet = 4;
	int numberOfParametersSet = 0;

	Config::setFromConfig(src, copyPath);
	if (src)
	{
		if (NumericalParameter* x = qobject_cast<NumericalParameter*>(src->getParameter("X")))
		{
			m_x.setValue(x->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* y = qobject_cast<NumericalParameter*>(src->getParameter("Y")))
		{
			m_y.setValue(y->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* w = qobject_cast<NumericalParameter*>(src->getParameter("Width")))
		{
			m_width.setValue(w->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* h = qobject_cast<NumericalParameter*>(src->getParameter("Height")))
		{
			m_height.setValue(h->getValue());
			numberOfParametersSet++;
		}
	}
	return numberOfParametersSet == numberOfParametersToSet;
}