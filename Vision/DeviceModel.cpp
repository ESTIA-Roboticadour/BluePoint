#include "DeviceModel.h"
#include "CameraFactory.h"

#include <QTimer>

DeviceModel::DeviceModel(const QString& cameraType, CameraConfig* cameraConfig, LightControlConfig* lightConfig, QObject* parent) :
	ModelBase(parent),
	m_cameraConfig(cameraConfig),
	m_lightConfig(lightConfig),
	m_camera(nullptr),
	m_isReleasing(false)
{
	setupCamera(cameraType, cameraConfig);
	setupConnections();
}

DeviceModel::~DeviceModel()
{
}

void DeviceModel::release()
{
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

void DeviceModel::restartOpenCamera()
{
	open();
}

void DeviceModel::restartCloseCamera()
{
	close();
}
