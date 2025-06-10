#pragma once
#include "ModelBase.h"
#include "CameraConfig.h"
#include "Camera.h"
#include "LightControlConfig.h"
#include "LightControl.h"

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
	LightControl* getLightControl() const { return m_lightControl; }

	void release() override;

	void openCamera();
	void closeCamera();

	void connectLight() const;

	void turnOnLight() const;
	void turnOffLight() const;

private slots:
	void onCameraReleased();
	void onCameraConnected();
	void onCameraDisconnected();
	void onCameraOpened();
	void onCameraClosed();
	void onCameraFailedToConnect(const QString& message);
	void onCameraFailedToDisconnect(const QString& message);
	void onCameraFailedToOpen(const QString& message);
	void onCameraFailedToClose(const QString& message);
	void onCameraErrorThrown(const QString& error, const QString& message);

	void onLightControlReleased();
	void onLightControlConnected(const QString& portName);
	void onLightControlConnectionFailed(const QString& portName, const QString& error);
	void onLightControlModuleInfoReceived(int id, int version);

	void restartOpenCamera();
	void restartCloseCamera();

private:
	void setupCamera(const QString& cameraType, CameraConfig* cameraConfig);
	void setupLightControl(LightControlConfig* lightConfig);
	void setupConnections();

signals:
	void cameraOpened();
	void cameraClosed();

	void imageProvided(const QImage& image);

	void lightControlConnected();
	void lightControlDisconnected();

private:
	CameraConfig* m_cameraConfig;
	LightControlConfig* m_lightConfig;
	Camera* m_camera;
	LightControl* m_lightControl;

	bool m_isReleasing;
	bool m_isLightOn;
};
