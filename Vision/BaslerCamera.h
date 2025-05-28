#pragma once
#include "Camera.h"

class BaslerCamera : public Camera
{
	Q_OBJECT

public:
	explicit BaslerCamera(QObject* parent = nullptr);
	~BaslerCamera() override;

	// Inherited via Camera
	bool isConnected() const override;
	bool isOpened() const override;
	void connect() override;
	void disconnect() override;
	void open() override;
	void close() override;
};
