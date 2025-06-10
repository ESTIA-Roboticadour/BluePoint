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
	if (!isReleased())
	{
		m_isReleasing = true;
		if (m_lightControl && !m_lightControl->isReleased())
		{
			m_lightControl->release();
		}
		else if (m_camera && !m_camera->isReleased())
		{
			m_camera->release();
		}
		else
		{
			ModelBase::release();
			m_isReleasing = false;
		}
	}
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
		connect(m_camera, &Camera::released, this, &DeviceModel::onCameraReleased);
		connect(m_camera, &Camera::connected, this, &DeviceModel::onCameraConnected);
		connect(m_camera, &Camera::disconnected, this, &DeviceModel::onCameraDisconnected);
		connect(m_camera, &Camera::opened, this, &DeviceModel::onCameraOpened);
		connect(m_camera, &Camera::closed, this, &DeviceModel::onCameraClosed);
		connect(m_camera, &Camera::failedToConnect, this, &DeviceModel::onCameraFailedToConnect);
		connect(m_camera, &Camera::failedToOpen, this, &DeviceModel::onCameraFailedToOpen);
		connect(m_camera, &Camera::failedToClose, this, &DeviceModel::onCameraFailedToClose);
		connect(m_camera, &Camera::failedToDisconnect, this, &DeviceModel::onCameraFailedToDisconnect);
		connect(m_camera, &Camera::errorThrown, this, &DeviceModel::onCameraErrorThrown);
		connect(m_camera, &Camera::imageProvided, this, &DeviceModel::imageProvided);
	}
	if (m_lightControl)
	{
		connect(m_lightControl, &LightControl::released, this, &DeviceModel::onLightControlReleased);
		connect(m_lightControl, &LightControl::connected, this, &DeviceModel::onLightControlConnected);
		connect(m_lightControl, &LightControl::connectionFailed, this, &DeviceModel::onLightControlConnectionFailed);
		connect(m_lightControl, &LightControl::disconnected, this, &DeviceModel::lightControlDisconnected);
		connect(m_lightControl, &LightControl::moduleInfoReceived, this, &DeviceModel::onLightControlModuleInfoReceived);
	}
}

void DeviceModel::openCamera()
{
	if (m_camera)
	{
		if (m_camera->isConnected())
		{
			if (m_camera->isOpened())
			{
				qInfo() << "Camera already opened";
			}
			else
			{
				m_camera->open(m_cameraConfig);
			}
		}
		else
		{
			m_camera->connect();
		}
	}
}

void DeviceModel::closeCamera()
{
	if (m_camera)
	{
		if (m_camera->isOpened())
			m_camera->close();

		if (m_camera->isConnected())
			m_camera->disconnect();
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

void DeviceModel::onCameraReleased()
{
	if (m_isReleasing)
		release();
}

void DeviceModel::onCameraConnected()
{
	qInfo() << "Camera connected successfully";
	m_isReleasing = false; // Reset releasing state
	openCamera();
}

void DeviceModel::onCameraDisconnected()
{
	qInfo() << "Camera disconnected successfully";
	emit cameraClosed();
	if (m_isReleasing)
		release();
}

void DeviceModel::onCameraOpened()
{
	qInfo() << "Camera opened successfully";
	emit cameraOpened();
}

void DeviceModel::onCameraClosed()
{
	qInfo() << "Camera closed successfully";
}

void DeviceModel::onCameraFailedToConnect(const QString& message)
{
	qWarning() << message;
	QTimer::singleShot(1000, this, &DeviceModel::restartOpenCamera);
}

void DeviceModel::onCameraFailedToDisconnect(const QString& message)
{
	qWarning() << message;
	QTimer::singleShot(1000, this, &DeviceModel::restartCloseCamera);
}

void DeviceModel::onCameraFailedToOpen(const QString& message)
{
	qWarning() << message;
	QTimer::singleShot(1000, this, &DeviceModel::restartOpenCamera);
}

void DeviceModel::onCameraFailedToClose(const QString& message)
{
	qWarning() << message;
	QTimer::singleShot(1000, this, &DeviceModel::restartCloseCamera);
}

void DeviceModel::onCameraErrorThrown(const QString& error, const QString& message)
{
	qWarning() << error + ": " + message;
}

void DeviceModel::restartOpenCamera()
{
	openCamera();
}

void DeviceModel::restartCloseCamera()
{
	closeCamera();
}

void DeviceModel::onLightControlReleased()
{
	if (m_isReleasing)
		release();
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
	qInfo() << "Light control id:" << id << " | Version: " << version;
}
