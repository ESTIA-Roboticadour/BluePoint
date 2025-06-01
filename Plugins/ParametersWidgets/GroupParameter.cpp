#include "GroupParameter.h"
#include "ParameterBase.h"
#include <QJsonValue>
#include <QJsonArray>

GroupParameter::GroupParameter(const QString& name, QObject* parent) :
	ParameterBase(name, parent),
	m_parameters()
{}

GroupParameter::GroupParameter(const GroupParameter& other, QObject* parent) :
    GroupParameter(other.getName(), other, parent)
{
}

GroupParameter::GroupParameter(const QString& name, const GroupParameter& other, QObject* parent) :
    ParameterBase(name, parent),
    m_parameters()
{
    for (const ParameterBase* p : other.m_parameters) {
        if (p)
            addParameter(p->copy(this));   // parent = this
    }
    setIsEditable(other.getIsEditable());

    //for (const auto* p : other.m_parameters)
    //{
    //    if (!p)
    //        continue;
    //    // Deep-copy via sérialisation (nécessite toJson()/fromJson())
    //    auto dup = ParameterBase::fromJson(p->toJson(), this);
    //    if (dup) m_parameters.append(dup.release());
    //}
}

GroupParameter::~GroupParameter()
{
	clearParameters();
}

void GroupParameter::setIsEditable(bool isEditable)
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

void GroupParameter::addParameter(ParameterBase* parameter)
{
	if (parameter && !m_parameters.contains(parameter))
	{
		m_parameters.append(parameter);
        connect(parameter, &ParameterBase::parameterChanged, this, &GroupParameter::onChildChanged);

        // pour ne pas avoir un disconnect sur un pointeur libéré
        connect(parameter, &QObject::destroyed, this, [this, parameter]{ m_parameters.removeOne(parameter); });
	}
}

void GroupParameter::removeParameter(ParameterBase* parameter)
{
	if (parameter && m_parameters.contains(parameter))
	{
        disconnect(parameter, &ParameterBase::parameterChanged, this, &GroupParameter::onChildChanged);
		m_parameters.removeOne(parameter);
	}
}

void GroupParameter::clearParameters()
{
    for (auto& parameter : m_parameters) {
        disconnect(parameter, &ParameterBase::parameterChanged, this, &GroupParameter::onChildChanged);
    }
	m_parameters.clear();
}

void GroupParameter::onChildChanged(const ParameterBase* sender)
{
    emit parameterChanged(sender);
}

QList<const ParameterBase*> GroupParameter::getParameters() const
{
	QList<const ParameterBase*> parameters(m_parameters.size());
	int i = 0;
	for (const auto& parameter : m_parameters)
	{
		parameters[i++] = parameter;
	}
	return parameters;
}

ParameterBase* GroupParameter::getParameter(const QString& name) const
{
    for (auto& param : m_parameters)
    {
        if (param->getName() == name)
            return param;
    }
    return nullptr;
}

ParameterBase* GroupParameter::copy(QObject* parent) const
{
    auto* g = new GroupParameter(this->getName(), parent);
    g->setIsEditable(getIsEditable());

    for (const ParameterBase* p : m_parameters)
    {
        // On passe 'g' comme parent pour respecter la hiérarchie QObject
        g->addParameter(p->copy(g));
    }
    return g;
}

QJsonObject GroupParameter::toJson() const
{
    QJsonArray arr;
    for (const auto* p : m_parameters)
        arr.append(p->toJson());

    return {{"type",        "group"},
            {"name",        getName()},
            {"parameters",  arr}};
}

std::unique_ptr<ParameterBase> GroupParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    auto g = std::make_unique<GroupParameter>(o["name"].toString(), parent);

    for (const QJsonValue& v : o["parameters"].toArray())
    {
        if (!v.isObject())
            continue;

        std::unique_ptr<ParameterBase> child = ParameterBase::fromJson(v.toObject(), g.get());

        if (child)
            g->addParameter(child.release());
    }
    return g;
}
