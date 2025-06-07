#include "ParameterBase.h"
#include "BoolParameter.h"
#include "NumericalParameter.h"
#include "StringParameter.h"
#include "ListParameter.h"
#include "GroupParameter.h"
#include "Matrix4x4Parameter.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>

ParameterBase::ParameterBase(const QString& name, QObject *parent) :
	QObject(parent),
	m_name(name),
	m_isEditable(true)
{}

QString ParameterBase::getName() const
{
	return m_name;
}

bool ParameterBase::getIsEditable() const
{
	return m_isEditable;
}

void ParameterBase::setIsEditable(bool isEditable)
{
	if (isEditable != m_isEditable)
	{
		m_isEditable = isEditable;
		emit isEditableChanged(m_isEditable);
	}
}

void ParameterBase::lock()
{
	setIsEditable(false);
}

void ParameterBase::unlock()
{
	setIsEditable(true);
}

std::unique_ptr<ParameterBase> ParameterBase::fromJson(const QJsonObject& o, QObject* parent)
{
    const QString type = o.value("type").toString();

    if (type == "bool")   return BoolParameter::fromJson(o, parent);
    if (type == "number") return NumericalParameter::fromJson(o, parent);
    if (type == "string") return StringParameter::fromJson(o, parent);
    if (type == "list")   return ListParameterBase::fromJson(o, parent);
    if (type == "group")  return GroupParameter::fromJson(o, parent);
    if (type == "matrix4X4") return Matrix4x4Parameter::fromJson(o, parent);

    return {};   // type inconnu
}
