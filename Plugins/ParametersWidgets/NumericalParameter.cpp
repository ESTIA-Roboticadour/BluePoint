#include "NumericalParameter.h"
#include <QJsonValue>

NumericalParameter::NumericalParameter(const QString& name, const double value, QObject* parent) :
	ParameterBase(name, parent),
	m_value(value),
	m_minimum(0.0),
	m_maximum(100.0),
	m_increment(1.)
{
	if (m_value < m_minimum)
	{
		m_minimum = m_value;
	}
	else if (m_value > m_maximum)
	{
		m_maximum = m_value;
	}
}

NumericalParameter::NumericalParameter(const NumericalParameter& parameter, QObject* parent) :
    ParameterBase(parameter.getName(), parent),
    m_value(0),
    m_minimum(parameter.m_minimum),
    m_maximum(parameter.m_maximum),
    m_increment(parameter.m_increment)
{
    setValue(parameter.m_value);
}

NumericalParameter::NumericalParameter(const QString& name, const NumericalParameter& parameter, QObject* parent) :
    ParameterBase(name, parent),
    m_value(0),
    m_minimum(parameter.m_minimum),
    m_maximum(parameter.m_maximum),
    m_increment(parameter.m_increment)
{
    setValue(parameter.m_value);
}

void NumericalParameter::setValue(double value)
{
	if (value < m_minimum)
	{
		internalSetValue(m_minimum);
	}
	else if (value > m_maximum)
	{
		internalSetValue(m_maximum);
	}
	else
	{
		internalSetValue(value);
	}
}

void NumericalParameter::internalSetValue(double value)
{

	if (getIsEditable() && m_value != value)
	{
		m_value = value;
		emit valueChanged(value);
        emit parameterChanged(this);
	}
}

void NumericalParameter::setMinimum(double minimum)
{
	if (getIsEditable() && minimum < m_maximum && m_minimum != minimum)
	{
		m_minimum = minimum;
		emit minimumChanged(m_minimum);

		if (m_value < m_minimum)
			setValue(m_minimum);
        else
            emit parameterChanged(this);
	}
}

void NumericalParameter::setMaximum(double maximum)
{
	if (getIsEditable() && maximum > m_minimum && m_maximum != maximum)
	{
		m_maximum = maximum;
		emit maximumChanged(m_maximum);

		if (m_value > m_maximum)
			setValue(m_maximum);
        else
            emit parameterChanged(this);
	}
}

void NumericalParameter::setIncrement(double increment)
{
	if (getIsEditable() && increment > 0. && m_increment != increment)
	{
		m_increment = increment;
		emit incrementChanged(m_increment);
        emit parameterChanged(this);
	}
}

void NumericalParameter::increment()
{
	if (getIsEditable())
	{
		setValue(m_value + m_increment);
	}
}

void NumericalParameter::decrement()
{
	if (getIsEditable())
	{
		setValue(m_value - m_increment);
	}
}

double NumericalParameter::getValue() const
{
	return m_value;
}

double NumericalParameter::getMinimum() const
{
	return m_minimum;
}

double NumericalParameter::getMaximum() const
{
	return m_maximum;
}

double NumericalParameter::getIncrement() const
{
	return m_increment;
}

ParameterBase* NumericalParameter::copy(QObject* parent) const
{
    return new NumericalParameter(*this, parent);
}

QJsonObject NumericalParameter::toJson() const
{
    return { {"type", "number"},
            {"name",  getName()},
            {"value", m_value},
            {"min",   m_minimum},
            {"max",   m_maximum},
            {"inc",   m_increment} };
}

std::unique_ptr<ParameterBase> NumericalParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    auto p = std::make_unique<NumericalParameter>(
        o["name"].toString(),
        0.,
        parent);
    p->setMinimum(o["min"].toDouble());
    p->setMaximum(o["max"].toDouble());
    p->setIncrement(o["inc"].toInt());
    p->setValue(o["value"].toDouble());
    return p;
}
