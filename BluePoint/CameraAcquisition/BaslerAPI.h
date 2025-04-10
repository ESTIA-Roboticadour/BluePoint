#pragma once
#include "pylon/PylonIncludes.h"

class BaslerAPI
{
public:
	static bool getFps(Pylon::CInstantCamera* camera, float& fps);
	static bool getWidth(Pylon::CInstantCamera* camera, int& width);
	static bool getHeight(Pylon::CInstantCamera* camera, int& height);

	static bool setFps(Pylon::CInstantCamera* camera, double fps);
	static bool setExposureTime(Pylon::CInstantCamera* camera, double exposureTime);
	static bool setWhiteBalanceOnce(Pylon::CInstantCamera* camera);
	static bool setPixelFormatBayerRG8(Pylon::CInstantCamera* camera);

	static bool maximizeAOI(Pylon::CInstantCamera* camera);
};
