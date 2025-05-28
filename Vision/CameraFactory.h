#pragma once
#include "Camera.h"
#include "CameraConfig.h"

#include <QObject>
#include <QString>

class CameraFactory
{
public:
	static Camera* createCamera(const QString& cameraType, CameraConfig* cameraConfig, QObject* parent=nullptr);
};

