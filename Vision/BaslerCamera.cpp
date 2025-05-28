#include "BaslerCamera.h"

BaslerCamera::BaslerCamera(QObject* parent) :
	Camera(parent)
{
}

BaslerCamera::~BaslerCamera()
{
	if (isConnected())
		disconnect();
}

bool BaslerCamera::isConnected() const
{
	return false;
}

bool BaslerCamera::isOpened() const
{
	return false;
}

void BaslerCamera::connect()
{
	emit failedToConnect("Not implemented");
	//emit connected();
}

void BaslerCamera::disconnect()
{
	emit disconnected();
}

void BaslerCamera::open()
{
	emit failedToOpen("Not implemented");
	//emit opened();
}

void BaslerCamera::close()
{
	emit closed();
}
