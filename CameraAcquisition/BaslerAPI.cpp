#include "BaslerAPI.h"
#include "GenApi/GenApi.h"

bool BaslerAPI::getFps(Pylon::CInstantCamera* camera, float& fps)
{
	GenApi::INodeMap& nodemap = camera->GetNodeMap();
	GenApi::CFloatPtr node = nodemap.GetNode("AcquisitionFrameRate");
	bool success = IsReadable(node);
	if (success)
		fps = static_cast<float>(node->GetValue());
	return success;
}

bool BaslerAPI::getWidth(Pylon::CInstantCamera* camera, int& width)
{
	GenApi::INodeMap& nodemap = camera->GetNodeMap();
	GenApi::CIntegerPtr node = nodemap.GetNode("Width");
	bool success = IsReadable(node);
	if (success)
		width = static_cast<int>(node->GetValue());
	return success;
}

bool BaslerAPI::getHeight(Pylon::CInstantCamera* camera, int& height)
{
	GenApi::INodeMap& nodemap = camera->GetNodeMap();
	GenApi::CIntegerPtr node = nodemap.GetNode("Height");
	bool success = IsReadable(node);
	if (success)
		height = static_cast<int>(node->GetValue());
	return success;
}

bool BaslerAPI::setFps(Pylon::CInstantCamera* camera, double fps)
{
	GenApi::INodeMap& nodemap = camera->GetNodeMap();

	// Activer le contrôle manuel du framerate
	GenApi::CBooleanPtr frameRateEnable = nodemap.GetNode("AcquisitionFrameRateEnable");
	if (IsWritable(frameRateEnable))
		frameRateEnable->SetValue(true);

	// Modifier le FPS
	GenApi::CFloatPtr fpsNode = nodemap.GetNode("AcquisitionFrameRate");
	bool success = IsWritable(fpsNode);
	if (success)
		fpsNode->SetValue(fps);
	return success;
}

bool BaslerAPI::setExposureTime(Pylon::CInstantCamera* camera, double exposureTime)
{
	GenApi::INodeMap& nodemap = camera->GetNodeMap();

	// Désactiver le mode automatique si actif
	GenApi::CEnumerationPtr exposureAuto = nodemap.GetNode("ExposureAuto");
	if (IsWritable(exposureAuto))
		exposureAuto->SetIntValue(exposureAuto->GetEntryByName("Off")->GetValue());

	// Définir le temps d’exposition
	GenApi::CFloatPtr exposureTimeNode = nodemap.GetNode("ExposureTime");
	bool success = IsWritable(exposureTimeNode);
	if (success)
		exposureTimeNode->SetValue(exposureTime);
	return success;
}

bool BaslerAPI::setWhiteBalanceOnce(Pylon::CInstantCamera* camera)
{
	GenApi::INodeMap& nodemap = camera->GetNodeMap();
	GenApi::CEnumerationPtr whiteBalanceNode = nodemap.GetNode("BalanceWhiteAuto");
	bool success = IsWritable(whiteBalanceNode);
	if (success)
		whiteBalanceNode->SetIntValue(whiteBalanceNode->GetEntryByName("Once")->GetValue());
	return success;
}

bool BaslerAPI::setPixelFormatBayerRG8(Pylon::CInstantCamera* camera)
{
	bool success = true;
	try
	{
		// Set the pixel data format.
		GenApi::INodeMap& nodemap = camera->GetNodeMap();
		Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("BayerRG8");
	}
	catch (const Pylon::GenericException& e)
	{
		success = false;
	}
	return success;
}

bool BaslerAPI::maximizeAOI(Pylon::CInstantCamera* camera)
{
	bool success = true;
	try
	{
		GenApi::INodeMap& nodemap = camera->GetNodeMap();

		// Get the parameters for setting the image area of interest (Image AOI).
		Pylon::CIntegerParameter width(nodemap, "Width");
		Pylon::CIntegerParameter height(nodemap, "Height");
		Pylon::CIntegerParameter offsetX(nodemap, "OffsetX");
		Pylon::CIntegerParameter offsetY(nodemap, "OffsetY");

		// Maximize the Image AOI.
		success &= offsetX.TrySetToMinimum(); // Set to minimum if writable.
		success &= offsetY.TrySetToMinimum(); // Set to minimum if writable.
		width.SetToMaximum();
		height.SetToMaximum();
	}
	catch (const Pylon::GenericException& e)
	{
		success = false;
	}
	return success;
}
