#include "LightControlController.h"
#include <QStringList>

LightControlController::LightControlController(LightControl* model, LightControlWindow* view, QObject* parent) :
	QObject(parent),
	m_model(model),
	m_view(view)
{
	connect(view, &LightControlWindow::portSelectedChanged, this, &LightControlController::onViewPortSelectedChanged);
	connect(view, &LightControlWindow::relayButtonPressed, model, &LightControl::toggleRelay);

	connect(model, &LightControl::disconnected, this, &LightControlController::onModelDisconnected);
	connect(model, &LightControl::connected, this, &LightControlController::onModelConnected);
	connect(model, &LightControl::connectionFailed, this, &LightControlController::onModelConnectionFailed);
	connect(model, &LightControl::relayStateChanged, view, &LightControlWindow::setRelayState);
	connect(model, &LightControl::moduleInfoReceived, view, &LightControlWindow::setModuleInfo);

	connect(view, &LightControlWindow::closeRequest, model, &LightControl::release);
	connect(model, &LightControl::released, this, &LightControlController::deleteLater);

	autoConnect();
}

LightControlController::~LightControlController()
{
	m_model->deleteLater();
	m_view->deleteLater();
}

void LightControlController::onModelDisconnected()
{
	m_view->setSelectedPort(-1);
	getAvailablePorts();
}

void LightControlController::onModelConnected(const QString& portName)
{
}

void LightControlController::onModelConnectionFailed(const QString& portName, const QString& error)
{
	m_view->setSelectedPort(-1);
}

void LightControlController::onViewPortSelectedChanged(const QString& portName)
{
	if (portName.isEmpty())
	{
		m_model->disconnect();
	}
	else 
	{
		m_model->connectToPort(portName);
	}
}

void LightControlController::getAvailablePorts() const
{
	m_view->setAvailablePorts(m_model->getAvailablePorts());
}

void LightControlController::autoConnect() const
{
	QStringList ports = m_model->getAvailablePorts();
	m_view->setAvailablePorts(ports);

	if (ports.size() == 0)
	{
		m_model->disconnect();
	}
	else if (ports.size() == 1)
	{
		m_view->setSelectedPort(0);
	}
	else
	{
		m_view->setSelectedPort(-1);
	}
}
