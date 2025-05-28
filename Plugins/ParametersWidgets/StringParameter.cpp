#include "StringParameter.h"
#include <QJsonValue>

StringParameter::StringParameter(const QString& name, const QString& value, Kind kind, QObject* parent) :
	ParameterBase(name, parent),
    m_value(value),
    m_kind(kind)
{
}

StringParameter::StringParameter(const StringParameter& parameter, QObject* parent):
    ParameterBase(parameter.getName(), parent),
    m_value(parameter.m_value),
    m_kind(parameter.m_kind)
{
}

StringParameter::StringParameter(const QString& name, const StringParameter& parameter, QObject* parent):
    ParameterBase(name, parent),
    m_value(parameter.m_value),
    m_kind(parameter.m_kind)
{
}

QString StringParameter::getValue() const
{
	return m_value;
}

StringParameter::Kind StringParameter::getKind() const
{
    return m_kind;
}

void StringParameter::setKind(Kind k)
{
    if (m_kind != k) {
        m_kind = k;
        emit kindChanged(m_kind);
        emit parameterChanged(this);
    }
}

void StringParameter::setValue(const QString& value)
{
	if (getIsEditable() && m_value != value)
	{
		m_value = value;
		emit valueChanged(m_value);
        emit parameterChanged(this);
	}
}

QJsonObject StringParameter::toJson() const
{
    return { {"type",  "string" },
            {"name",  getName()},
            {"value", m_value},
            {"kind",  static_cast<int>(m_kind)} };
}

std::unique_ptr<ParameterBase> StringParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    return std::make_unique<StringParameter>(
        o["name"].toString(),
        o["value"].toString(),
        static_cast<Kind>(o.value("kind").toInt()),
        parent);
}
