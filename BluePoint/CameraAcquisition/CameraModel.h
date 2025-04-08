#pragma once
#include "CameraProcessor.h"

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QSize>

class CameraModel : public QObject 
{
	Q_OBJECT

public:
	explicit CameraModel(CameraProcessor* cameraProcessor, QObject* parent = nullptr);

public slots:
	void openCamera();
	void closeCamera();
	void startRecording(const QString& filename);
	void stopRecording();
	void setWorkDimensions(const QSize& size);

public:
	const CameraProcessor* getCameraProcessor() const;
	void setCameraProcessor(CameraProcessor* cameraProcessor);

private:
	void setupCameraProcessorConnections() const;
	void unsetupCameraProcessorConnections() const;

signals:
	void deviceConnected();
	void deviceDisconnected();
	void recordingStarted(const QString& filename);
	void recordingStopped();
	void newFrameCaptured(const QImage& image);
	void errorThrown(const QString& error, const QString& errorMessage);
	void dimensionsChanged(int width, int height);
	void fpsChanged(float fps);

private:
	CameraProcessor* m_cameraProcessor;
};
