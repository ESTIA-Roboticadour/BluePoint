#include "ModelBase.h"

ModelBase::ModelBase(QObject* parent) :
	QObject(parent),
	m_isRelease(false)
{
}

bool ModelBase::isReleased() const
{
	return m_isRelease;
}

void ModelBase::release()
{
	if (!m_isRelease)
	{
		m_isRelease = true;
		emit released();
	}
}
