#include "BoolParameter.h"

BoolParameter::BoolParameter(const QString& name, const bool value, QObject* parent) :
	ParameterBase(name, parent),
	m_value(value)
{
}

bool BoolParameter::getValue() const
{
	return m_value;
}

void BoolParameter::setValue(bool value)
{
	if (getIsEditable() && m_value != value)
	{
		m_value = value;
		emit valueChanged(m_value);
	}
}
