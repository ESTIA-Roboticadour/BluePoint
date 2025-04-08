#pragma once

#include <QObject>
#include <QString>
#include <QImage>

class CameraProcessor : public QObject 
{
	Q_OBJECT

public:
	explicit CameraProcessor(QObject* parent = nullptr);
	~CameraProcessor() = default;

public slots:
	int getWidth() const;
	int getHeight() const;
	float getFps() const;

	int getWorkWidth() const;
	int getWorkHeight() const;
	QSize getWorkDimensions() const;

	void setWorkWidth(int width);
	void setWorkHeight(int height);
	void setWorkDimensions(int width, int height);
	void setWorkDimensions(const QSize& size);

	virtual void open() = 0;
	virtual void close() = 0;
	virtual void startRecording(const QString& filename) = 0;
	virtual void stopRecording() = 0;

protected:
	void setWidth(int width);
	void setHeight(int height);
	void setFps(float fps);

	void findNewSizeToKeepAspectRatio(int originalWidth, int originalHeight, int& width, int& height) const;

signals:
	void deviceConnected();
	void deviceDisconnected();
	void recordingStarted(const QString& filename);
	void recordingStopped();
	void newFrameCaptured(const QImage& image);
	void errorThrown(const QString& error, const QString& errorMessage);
	void dimensionsChanged(int width, int height);
	void workDimensionsChanged(int width, int height);
	void fpsChanged(float fps);

private:
	int m_width;
	int m_height;
	float m_fps;
	int m_workWidth;
	int m_workHeight;
};
