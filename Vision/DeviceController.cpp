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
	m_model->openCamera();
	m_view->setCameraConfig(m_model->getCameraConfig());
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
	connect(m_model, &DeviceModel::imageProvided, m_view, &DeviceView::onImageProvided);

	connect(m_view, &DeviceView::isDestroying, this, &DeviceController::onViewDestroying);
	connect(m_view, &DeviceView::lightOnRequested, this, &DeviceController::onLightOnRequested);
	connect(m_view, &DeviceView::lightOffRequested, this, &DeviceController::onLightOffRequested);
}

void DeviceController::onViewDestroying()
{
	m_model->release();
	
	disconnect(m_view, &DeviceView::isDestroying, this, &DeviceController::onViewDestroying);
	disconnect(m_view, &DeviceView::lightOnRequested, this, &DeviceController::onLightOnRequested);
	disconnect(m_view, &DeviceView::lightOffRequested, this, &DeviceController::onLightOffRequested);
}

void DeviceController::onModelReleased()
{
	deleteLater();

	disconnect(m_model, &DeviceModel::lightControlConnected, this, &DeviceController::onLightConnected);
	disconnect(m_model, &DeviceModel::lightControlDisconnected, this, &DeviceController::onLightDisconnected);
	disconnect(m_model, &DeviceModel::imageProvided, this, &DeviceController::onImageProvided);
	disconnect(m_model, &DeviceModel::released, this, &DeviceController::onModelReleased);
}

void DeviceController::onImageProvided(const QImage& image)
{
	if (m_view)
		m_view->onImageProvided(image);
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
}
