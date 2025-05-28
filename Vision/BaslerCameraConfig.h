#pragma once
#include "CameraConfig.h"

class BaslerCameraConfig : public CameraConfig
{
	Q_OBJECT

public:
	explicit BaslerCameraConfig(QObject* parent = nullptr);
	BaslerCameraConfig(const BaslerCameraConfig& config, QObject* parent = nullptr);
	~BaslerCameraConfig() override = default;

protected:
	bool setFromConfig(const Config* src) override;

private:
	void defineBounds();
	void addParameters();
};
