#include "DeviceController.h"

DeviceController::DeviceController(DeviceModel* model, DeviceView* view, QObject* parent) : 
	WidgetControllerBase(model, view, parent),
	m_model(model),
	m_view(view)
{
	setupConnections();
}

DeviceController::~DeviceController()
{
	m_model->deleteLater();
}

void DeviceController::setupConnections()
{
	connect(m_model, &DeviceModel::released, this, &DeviceController::onModelReleased);
}

void DeviceController::onModelReleased()
{
	deleteLater();
}

void DeviceController::onViewDestroyed()
{
	m_view = nullptr;
	m_model->release();
}
