#include "ViewFactory.h"
#include "CameraController.h"
#include "CameraModel.h"

CameraWindow* ViewFactory::createCameraWindow(CameraReader* reader)
{
    auto* model = new CameraModel(reader);
    auto* view = new CameraWindow();
    auto* controller = new CameraController(view, model);
    return view;
}
