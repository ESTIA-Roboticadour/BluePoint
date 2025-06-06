#include "ConfigurationController.h"
#include <QFile>

ConfigurationController::ConfigurationController(ConfigurationModel* model, ConfigurationView* view, QObject* parent) :
	WidgetControllerBase(model, view, parent),
	m_model(model),
	m_view(view)
{
	setupConnections();
	m_view->setConfig(m_model->getEditableConfig());
}

ConfigurationController::~ConfigurationController()
{
	m_model->deleteLater();
}

void ConfigurationController::setupConnections()
{
	connect(m_model, &ConfigurationModel::released, this, &ConfigurationController::onModelReleased);

	connect(m_model, &ConfigurationModel::changed, m_view, &ConfigurationView::onConfigModified);
	connect(m_model, &ConfigurationModel::saved, m_view, &ConfigurationView::onConfigSaved);
	connect(m_model, &ConfigurationModel::canceled, m_view, &ConfigurationView::onConfigCanceled);

	connect(m_view, &ConfigurationView::cancelRequested, m_model, &ConfigurationModel::cancel);
	connect(m_view, &ConfigurationView::resetRequested, m_model, &ConfigurationModel::reset);
	connect(m_view, &ConfigurationView::saveRequested, m_model, &ConfigurationModel::save);
	connect(m_view, &ConfigurationView::openRequested, m_model, &ConfigurationModel::open);
}

void ConfigurationController::onModelReleased()
{
	deleteLater();
}

void ConfigurationController::onViewDestroyed()
{
	m_view = nullptr;
	m_model->release();
}
