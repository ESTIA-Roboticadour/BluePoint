#include "LightControlModel.h"
#include "LightControlWindow.h"
#include "LightControlController.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    auto* model = new LightControlModel;
    auto* window = new LightControlWindow;
    auto* controller = new LightControlController(model, window);

    window->show();
    return a.exec();
}
