#include "WidgetControllerBase.h"

WidgetControllerBase::WidgetControllerBase(ModelBase* model, QWidget* view, QObject* parent) :
	QObject(parent),
	m_view(view),
	m_model(model)
{
	setupConnections();
}

void WidgetControllerBase::setupConnections()
{
	connect(m_view, &QWidget::destroyed, this, &WidgetControllerBase::onViewDestroyed);
}
