#include "WindowControllerBase.h"

WindowControllerBase::WindowControllerBase(ModelBase* model, WindowBase* view, QObject* parent) :
	QObject(parent),
	m_view(view),
	m_model(model)
{
	setupConnections();
}

void WindowControllerBase::setupConnections()
{
	connect(m_view, &WindowBase::closeRequested, this, &WindowControllerBase::onViewCloseRequested);
}
