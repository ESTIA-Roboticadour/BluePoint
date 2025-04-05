#pragma once

#include <QObject>
#include <QString>
#include <QPixmap>

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

	virtual void open() = 0;
	virtual void close() = 0;
	virtual void startRecording(const QString& filename) = 0;
	virtual void stopRecording() = 0;

protected:
	void setWidth(int width);
	void setHeight(int height);
	void setFps(float fps);

signals:
	void deviceConnected();
	void deviceDisconnected();
	void recordingStarted(const QString& filename);
	void recordingStopped();
	void newFrameCaptured(const QPixmap& pixmap);
	void errorThrown(const QString& error, const QString& errorMessage);
	void dimensionsChanged(int width, int height);
	void fpsChanged(float fps);

private:
	int m_width;
	int m_height;
	float m_fps;
};
