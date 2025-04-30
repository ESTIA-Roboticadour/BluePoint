#include "ParameterBase.h"

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
