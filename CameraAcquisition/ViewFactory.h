#pragma once
#include "CameraProcessor.h"
#include "CameraWindow.h"

class ViewFactory
{
public:
	static CameraWindow* createCameraWindow(CameraProcessor* reader);
};
