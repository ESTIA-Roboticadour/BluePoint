#pragma once
#include "CameraReader.h"
#include "CameraWindow.h"

class ViewFactory
{
public:
	static CameraWindow* createCameraWindow(CameraReader* reader);
};
