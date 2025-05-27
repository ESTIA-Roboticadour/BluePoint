#include "StringParameter.h"
#include <QJsonValue>

StringParameter::StringParameter(const QString& name, const QString& value, QObject* parent) :
	ParameterBase(name, parent),
	m_value(value)
{
}

StringParameter::StringParameter(const StringParameter& parameter, QObject* parent):
    ParameterBase(parameter.getName(), parent),
    m_value(parameter.m_value)
{
}

StringParameter::StringParameter(const QString& name, const StringParameter& parameter, QObject* parent):
    ParameterBase(name, parent),
    m_value(parameter.m_value)
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
        emit parameterChanged();
	}
}

QJsonObject StringParameter::toJson() const
{
    return { {"type",  "string" },
            {"name",  getName()},
            {"value", m_value} };
}

std::unique_ptr<ParameterBase> StringParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    return std::make_unique<StringParameter>(
        o["name"].toString(),
        o["value"].toString(),
        parent);
}
