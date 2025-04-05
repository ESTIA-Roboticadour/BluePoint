#include "ViewFactory.h"
#include "WebcamProcessor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	WebcamProcessor* webcam = new WebcamProcessor();
	CameraWindow* view = ViewFactory::createCameraWindow(webcam);

	view->show();
	return a.exec();
}
