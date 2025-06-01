#pragma once
#include "Config.h"
#include "NumericalParameter.h"
#include <QRect>
#include <QSize>
#include <QPoint>

class RoiConfig : public Config
{
	Q_OBJECT

public:
	explicit RoiConfig(QObject* parent = nullptr);
	RoiConfig(int x, int y, int w, int h, QObject* parent = nullptr);
	RoiConfig(const RoiConfig& config, QObject* parent = nullptr);
	~RoiConfig() override = default;

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	QPoint getPos() const;
	QSize getSize() const;
	QRect getRoi() const;

	void setX(const int x);
	void setY(const int y);
	void setWidth(const int w);
	void setHeight(const int h);
	void setPos(const int x, const int y);
	void setPos(const QPoint& pos);
	void setSize(const int w, const int h);
	void setSize(const QSize& size);
	void setRoi(const QRect& roi);
	void setRoi(const int x, const int y, const int width, const int height);

	void reset() override;

protected:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void defineBounds();
	void addParameters();

private:
	NumericalParameter m_x;
	NumericalParameter m_y;
	NumericalParameter m_width;
	NumericalParameter m_height;
};
