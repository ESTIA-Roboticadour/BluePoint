#include "StringParameter.h"


StringParameter::StringParameter(const QString& name, const QString& value, QObject* parent) :
	ParameterBase(name, parent),
	m_value(value)
{
}

QString StringParameter::getValue() const
{
	return m_value;
}

void StringParameter::setValue(const QString& value)
{
	if (getIsEditable() && m_value != value)
	{
		m_value = value;
		emit valueChanged(m_value);
	}
}
