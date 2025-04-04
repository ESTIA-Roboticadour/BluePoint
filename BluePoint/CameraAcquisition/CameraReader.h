#pragma once

#include <QObject>
#include <QString>
#include <QPixmap>

class CameraReader : public QObject 
{
    Q_OBJECT

public:
    explicit CameraReader(int device = 0, QObject* parent = nullptr);
    ~CameraReader() = default;

public slots:
    int getWidth() const;
    int getHeight() const;
    int getFps() const;

    void setDevice(int device);
    int getDevice() const;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void startRecording(const QString& filename) = 0;
    virtual void stopRecording() = 0;

protected:
    void setWidth(int width);
    void setHeight(int height);
    void setFps(int fps);

signals:
    void deviceConnected();
    void deviceDisconnected();
    void recordingStarted(const QString& filename);
    void recordingStopped();
    void newFrameCaptured(const QPixmap& pixmap);
    void errorThrown(const QString& error, const QString& errorMessage);
    void dimensionsChanged(int width, int height);
    void fpsChanged(int fps);
    void deviceChanged(int device);

private:
    int m_device;
    int m_width;
    int m_height;
    int m_fps;
};
