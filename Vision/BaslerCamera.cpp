#include "BaslerCamera.h"

BaslerCamera::BaslerCamera(QObject* parent) :
	Camera(parent)
{
}

BaslerCamera::~BaslerCamera()
{
	if (isOpened())
		close();
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
	emit connected();
}

void BaslerCamera::disconnect()
{
	emit disconnected();
}

void BaslerCamera::open()
{
	emit opened();
}

void BaslerCamera::close()
{
	emit closed();
}
