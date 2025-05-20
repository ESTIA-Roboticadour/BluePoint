#pragma once

#include "MainModel.h"
#include "MainWindow.h"
#include "MainController.h"

class ViewFactory
{
public:
	static MainWindow* createMainWindow();
};

