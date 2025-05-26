#pragma once
#include "Config.h"
#include "NumericalParameter.h"

class CameraConfig : public Config
{
	Q_OBJECT

public:
	explicit CameraConfig(QObject* parent = nullptr);
	CameraConfig(int width, int height, int fps, QObject* parent = nullptr);
	CameraConfig(const CameraConfig& config, QObject* parent = nullptr);
	~CameraConfig() override = default;

	int getWidth() const;
	int getHeight() const;
	int getFps() const;

	void setWidth(const int width);
	void setHeight(const int height);
	void setFps(const int fps);

private:
	void defineBounds();
	void addParameters();

protected:
	NumericalParameter m_width;
	NumericalParameter m_height;
	NumericalParameter m_fps;
};
