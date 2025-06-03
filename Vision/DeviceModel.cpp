#include "DeviceModel.h"
#include "CameraFactory.h"

#include <QTimer>

DeviceModel::DeviceModel(const QString& cameraType, CameraConfig* cameraConfig, LightControlConfig* lightConfig, QObject* parent) :
	ModelBase(parent),
	m_cameraConfig(cameraConfig),
	m_lightConfig(lightConfig),
	m_camera(nullptr),
	m_isReleasing(false),
	m_isLightOn(false)
{
	setupCamera(cameraType, cameraConfig);
	setupLightControl(lightConfig);
	setupConnections();
}

DeviceModel::~DeviceModel()
{
}

void DeviceModel::release()
{
	if (m_lightControl)
	{
		m_lightControl->release();
	}

	if (m_camera && m_camera->isOpened())
	{
		m_isReleasing = true;
		m_camera->close();
	}
	else
	{
		ModelBase::release();
	}
}

void DeviceModel::open()
{
	if (m_camera && !m_camera->isOpened())
	{
		m_camera->open();
	}
}

void DeviceModel::close()
{
	if (m_camera && m_camera->isOpened())
	{
		m_camera->close();
	}
}

void DeviceModel::connectLight() const
{
	if (m_lightControl)
		m_lightControl->connectToPort(m_lightConfig->getComPort());
}

void DeviceModel::turnOnLight() const
{
	if (m_lightControl)
		m_lightControl->setRelay(m_lightConfig->getRelay() - 1, true);
}

void DeviceModel::turnOffLight() const
{
	if (m_lightControl)
		m_lightControl->setRelay(m_lightConfig->getRelay() - 1, false);
}

void DeviceModel::setupCamera(const QString& cameraType, CameraConfig* cameraConfig)
{
	if (m_camera)
	{
		qWarning() << "Camera already set";
	}
	else if (!cameraConfig)
	{
		qWarning() << "Camera config is empty";
	}
	else
	{
		m_camera = CameraFactory::createCamera(cameraType, cameraConfig, this);
		if (!m_camera)
			qCritical() << "Camera not created";
	}
}

void DeviceModel::setupLightControl(LightControlConfig* lightConfig)
{
	if (lightConfig)
	{
		m_lightConfig = lightConfig;
		m_lightControl = new LightControl(this);
	}
	else
		qWarning() << "Light control config is empty";
}

void DeviceModel::setupConnections()
{
	if (m_camera)
	{
		connect(m_camera, &Camera::opened, this, &DeviceModel::onCameraOpened);
		connect(m_camera, &Camera::closed, this, &DeviceModel::onCameraClosed);
		connect(m_camera, &Camera::failedToOpen, this, &DeviceModel::onCameraFailedToOpen);
		connect(m_camera, &Camera::failedToClose, this, &DeviceModel::onCameraFailedToClose);
		connect(m_camera, &Camera::errorThrown, this, &DeviceModel::onCameraErrorThrown);
	}
	if (m_lightControl)
	{
		connect(m_lightControl, &LightControl::connected, this, &DeviceModel::onLightControlConnected);
		connect(m_lightControl, &LightControl::connectionFailed, this, &DeviceModel::onLightControlConnectionFailed);
		connect(m_lightControl, &LightControl::disconnected, this, &DeviceModel::lightControlDisconnected);
		connect(m_lightControl, &LightControl::moduleInfoReceived, this, &DeviceModel::onLightControlModuleInfoReceived);
	}
}

void DeviceModel::onCameraOpened()
{
	qInfo() << "Camera opened successfully.";
	m_isReleasing = false; // Reset releasing state
	emit cameraOpened();
}

void DeviceModel::onCameraClosed()
{
	qInfo() << "Camera closed successfully.";
	emit cameraClosed();
	if (m_isReleasing)
		ModelBase::release();
}

void DeviceModel::onCameraFailedToOpen(const QString& message)
{
	qWarning() << "Failed to open camera:" << message;
	QTimer::singleShot(1000, this, &DeviceModel::restartOpenCamera);
}

void DeviceModel::onCameraFailedToClose(const QString& message)
{
	qWarning() << "Failed to close camera:" << message;
	QTimer::singleShot(1000, this, &DeviceModel::restartCloseCamera);
}

void DeviceModel::onCameraErrorThrown(const QString& error, const QString& message)
{
	qWarning() << "Camera error:" << error << "Message:" << message;
}

void DeviceModel::onLightControlConnected(const QString& portName)
{
	qInfo() << "Light control connected on port:" << portName;
	emit lightControlConnected();
}

void DeviceModel::onLightControlConnectionFailed(const QString& portName, const QString& error)
{
	qWarning() << "Light control connection failed on port:" << portName << "Error:" << error;
}

void DeviceModel::onLightControlModuleInfoReceived(int id, int version)
{
	qInfo() << "Light control id:" << id  << " | Version: " << version;
}

void DeviceModel::restartOpenCamera()
{
	open();
}

void DeviceModel::restartCloseCamera()
{
	close();
}
