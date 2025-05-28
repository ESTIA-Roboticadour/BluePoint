#include "BoolParameter.h"
#include <QJsonValue>

BoolParameter::BoolParameter(const QString& name, const bool value, QObject* parent) :
	ParameterBase(name, parent),
	m_value(value)
{
}

BoolParameter::BoolParameter(const BoolParameter& parameter, QObject* parent):
    ParameterBase(parameter.getName(), parent),
    m_value(parameter.m_value)
{
}

BoolParameter::BoolParameter(const QString& name, const BoolParameter& parameter, QObject* parent):
    ParameterBase(name, parent),
    m_value(parameter.m_value)
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
        emit parameterChanged(this);
	}
}

QJsonObject BoolParameter::toJson() const
{
    return { {"type", "bool"},
            {"name",  getName()},
            {"value", m_value} };
}

std::unique_ptr<ParameterBase> BoolParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    return std::make_unique<BoolParameter>(
        o["name"].toString(),
        o["value"].toBool(),
        parent);
}
