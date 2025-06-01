#include "StringParameter.h"
#include <QJsonValue>

StringParameter::StringParameter(const QString& name, const QString& value, Kind kind, QObject* parent) :
	ParameterBase(name, parent),
    m_value(value),
    m_kind(kind),
    m_canEditPath(true)
{
}

StringParameter::StringParameter(const StringParameter& parameter, QObject* parent):
    ParameterBase(parameter.getName(), parent),
    m_value(parameter.m_value),
    m_kind(parameter.m_kind),
    m_canEditPath(parameter.m_canEditPath)
{
}

StringParameter::StringParameter(const QString& name, const StringParameter& parameter, QObject* parent):
    ParameterBase(name, parent),
    m_value(parameter.m_value),
    m_kind(parameter.m_kind),
    m_canEditPath(parameter.m_canEditPath)
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

 bool StringParameter::getCanEditPath() const
{
    return m_canEditPath;
}

ParameterBase* StringParameter::copy(QObject* parent) const
{
    return new StringParameter(*this, parent);
}

void StringParameter::setKind(Kind k)
{
    if (m_kind != k) {
        m_kind = k;
        emit kindChanged(m_kind);
        emit parameterChanged(this);
    }
}

void StringParameter::setCanEditPath(bool canEditPath)
{
    if (m_canEditPath != canEditPath)
    {
        m_canEditPath = canEditPath;
        emit canEditPathChanged(m_canEditPath);
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
