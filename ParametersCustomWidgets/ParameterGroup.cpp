#include "ParameterGroup.h"

ParameterGroup::ParameterGroup(const QString& name, QObject* parent) :
	ParameterBase(name, parent),
	m_parameters()
{}

ParameterGroup::~ParameterGroup()
{
	clearParameters();
}

void ParameterGroup::setIsEditable(bool isEditable)
{
	if (getIsEditable() != isEditable)
	{
		for (auto& parameter : m_parameters)
		{
			parameter->setIsEditable(isEditable);
		}
		ParameterBase::setIsEditable(isEditable);
	}
}

void ParameterGroup::addParameter(ParameterBase* parameter)
{
	if (parameter && !m_parameters.contains(parameter))
	{
		m_parameters.append(parameter);
	}
}

void ParameterGroup::removeParameter(ParameterBase* parameter)
{
	if (parameter && m_parameters.contains(parameter))
	{
		m_parameters.removeOne(parameter);
	}
}

void ParameterGroup::clearParameters()
{
	m_parameters.clear();
}

QList<const ParameterBase*> ParameterGroup::getParameters() const
{
	QList<const ParameterBase*> parameters(m_parameters.size());
	int i = 0;
	for (const auto& parameter : m_parameters)
	{
		parameters[i++] = parameter;
	}
	return parameters;
}
