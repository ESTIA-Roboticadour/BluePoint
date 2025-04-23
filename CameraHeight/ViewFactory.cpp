#include "ViewFactory.h"
#include "CameraHeightModel.h"
#include "CameraHeightController.h"

CameraHeightWindow* ViewFactory::createCameraHeightWindow()
{
    auto* model = new CameraHeightModel();
    auto* view = new CameraHeightWindow();
    auto* controller = new CameraHeightController(view, model);
    return view;
}
