// CameraController.h
#pragma once

#include <QObject>
#include "CameraModel.h"
#include "CameraWindow.h"

class CameraController : public QObject 
{
    Q_OBJECT

public:
    explicit CameraController(CameraWindow* view, CameraModel* model, QObject* parent = nullptr);
    ~CameraController();

private slots:
    void onViewClosing();
    void onStartRecordingCamera();
    void onDimensionsChanged(int width, int height);
    void onFpsChanged(int fps);

private:
    CameraWindow* m_view;
    CameraModel* m_model;
};
