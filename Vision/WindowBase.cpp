#include "WindowBase.h"

WindowBase::WindowBase(QWidget* parent) :
	QMainWindow(parent)
{
}

void WindowBase::closeEvent(QCloseEvent* event)
{
	event->ignore();
	emit closeRequested();
}
