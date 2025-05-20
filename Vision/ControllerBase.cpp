#include "ControllerBase.h"

ControllerBase::ControllerBase(ModelBase* model, QObject* parent) : 
	QObject(parent),
	m_model(model)
{
}
