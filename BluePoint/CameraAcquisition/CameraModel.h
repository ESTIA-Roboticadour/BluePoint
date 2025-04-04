#pragma once
#include "CameraReader.h"

#include <QObject>
#include <QString>
#include <QPixmap>

class CameraModel : public QObject 
{
    Q_OBJECT

public:
    explicit CameraModel(CameraReader* reader, QObject* parent = nullptr);

public slots:
    void openCamera();
    void closeCamera();
    void startRecording(const QString& filename);
    void stopRecording();
    void setDevice(int device);

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
    CameraReader* m_cameraReader;
};
