#include "DeviceController.h"
#include "LightControlConfig.h"
#include "LightControl.h"

DeviceController::DeviceController(DeviceModel* model, DeviceView* view, QObject* parent) :
	WidgetControllerBase(model, view, parent),
	m_model(model),
	m_view(view)
{
	m_view->setButtonsState(false);
	setupConnections();

	m_model->connectLight();
}

DeviceController::~DeviceController()
{
	m_model->deleteLater();
}

void DeviceController::setupConnections()
{
	connect(m_model, &DeviceModel::released, this, &DeviceController::onModelReleased);

	connect(m_model, &DeviceModel::lightControlConnected, this, &DeviceController::onLightConnected);
	connect(m_model, &DeviceModel::lightControlDisconnected, this, &DeviceController::onLightDisconnected);

	connect(m_view, &DeviceView::lightOnRequested, this, &DeviceController::onLightOnRequested);
	connect(m_view, &DeviceView::lightOffRequested, this, &DeviceController::onLightOffRequested);
}

void DeviceController::onModelReleased()
{
	deleteLater();
}

void DeviceController::onLightConnected() const
{
	m_view->setButtonsState(true);
	const LightControlConfig* lightConfig = m_model->getLightConfig();
	m_view->setLightInfo(lightConfig->getComPort(), lightConfig->getRelay());
}

void DeviceController::onLightDisconnected() const
{
	m_view->setButtonsState(false);
}

void DeviceController::onLightOnRequested() const
{
	m_model->turnOnLight();
}

void DeviceController::onLightOffRequested() const
{
	m_model->turnOffLight();
}

void DeviceController::onViewDestroyed()
{
	m_view = nullptr;
	m_model->release();
}
