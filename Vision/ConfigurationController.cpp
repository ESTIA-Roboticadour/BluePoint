#include "ConfigurationController.h"

ConfigurationController::ConfigurationController(ConfigurationModel* model, ConfigurationView* view, QObject* parent) :
	WidgetControllerBase(model, view, parent),
	m_model(model),
	m_view(view)
{
	setupConnections();
}

ConfigurationController::~ConfigurationController()
{
	m_model->deleteLater();
}

void ConfigurationController::setupConnections()
{
	connect(m_model, &ConfigurationModel::released, this, &ConfigurationController::onModelReleased);
	connect(m_view, &ConfigurationView::cancelRequested, this, &ConfigurationController::onCancelRequested);
	connect(m_view, &ConfigurationView::resetRequested, this, &ConfigurationController::onResetRequested);
	connect(m_view, &ConfigurationView::saveRequested, this, &ConfigurationController::onSaveRequested);
}

void ConfigurationController::onModelReleased()
{
	deleteLater();
}

void ConfigurationController::onCancelRequested()
{
}

void ConfigurationController::onResetRequested()
{
}

void ConfigurationController::onSaveRequested(const QString& path)
{
	bool saved = m_model->save(path);
}

void ConfigurationController::onViewDestroyed()
{
	m_view = nullptr;
	m_model->release();
}
