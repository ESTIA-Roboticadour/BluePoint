#include "NumericalParameter.h"

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
	}
}

void NumericalParameter::setIncrement(double increment)
{
	if (getIsEditable() && increment > 0. && m_increment != increment)
	{
		m_increment = increment;
		emit incrementChanged(m_increment);
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

int NumericalParameter::getIncrement() const
{
	return m_increment;
}
