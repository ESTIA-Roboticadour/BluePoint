#pragma once
#include "CameraConfig.h"
#include "NumericalParameter.h"

class RealSenseCameraConfig : public CameraConfig
{
	Q_OBJECT

public:
	explicit RealSenseCameraConfig(QObject* parent = nullptr);
	RealSenseCameraConfig(const RealSenseCameraConfig& config, QObject* parent = nullptr);
	~RealSenseCameraConfig() override = default;

	void reset() override;
	Config* copy(QObject* parent = nullptr) const override;

protected:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void defineBounds();
	void addParameters();

private:
	NumericalParameter m_test;
};

