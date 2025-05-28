#pragma once
#include "ModelBase.h"
#include "CameraConfig.h"
#include "LightControlConfig.h"
#include "Camera.h"

#include <QString>

class DeviceModel : public ModelBase
{
	Q_OBJECT
public:
	explicit DeviceModel(const QString& cameraType, CameraConfig* cameraConfig, LightControlConfig* lightConfig, QObject* parent=nullptr);
	~DeviceModel() override;

	CameraConfig* getCameraConfig() const { return m_cameraConfig; }
	LightControlConfig* getLightConfig() const { return m_lightConfig; }
	Camera* getCamera() const { return m_camera; }

	void release() override;

	void open();
	void close();

private slots:
	void onCameraOpened();
	void onCameraClosed();
	void onCameraFailedToOpen(const QString& message);
	void onCameraFailedToClose(const QString& message);
	void onCameraErrorThrown(const QString& error, const QString& message);

	void restartOpenCamera();
	void restartCloseCamera();

private:
	void setupCamera(const QString& cameraType, CameraConfig* cameraConfig);
	void setupConnections();

signals:
	void cameraOpened();
	void cameraClosed();

private:
	CameraConfig* m_cameraConfig;
	LightControlConfig* m_lightConfig;
	Camera* m_camera;

	bool m_isReleasing;
};
