#include "ViewFactory.h"
#include "CameraController.h"
#include "CameraModel.h"

CameraWindow* ViewFactory::createCameraWindow(CameraProcessor* cameraProcessor)
{
	auto* model = new CameraModel(cameraProcessor);
	auto* view = new CameraWindow();
	auto* controller = new CameraController(view, model);
	return view;
}
