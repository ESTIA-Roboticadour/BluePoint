#pragma once
#include "CameraConfig.h"
#include "ListParameter.h"
#include "NumericalParameter.h"

#include <QString>
#include <QStringList>

class BaslerCameraConfig : public CameraConfig
{
	Q_OBJECT

public:
	explicit BaslerCameraConfig(QObject* parent = nullptr);
	BaslerCameraConfig(const BaslerCameraConfig& config, QObject* parent = nullptr);
	~BaslerCameraConfig() override = default;

	int getMaximumWidth() const;
	int getMaximumHeight() const;

	int getOffsetX() const;
	int getOffsetY() const;

	QString getSelectedFormat() const;
	QStringList getFormats() const;

	int getExposureTime() const;
	int getGainDB() const;

	void reset() override;
	Config* copy(QObject* parent = nullptr) override;

protected:
	bool setFromConfig(const Config* src, bool copyPath) override;

private slots:
	void setBoundsByMaximums();
	void boundWidthByMaxWidthAndOffsetX();
	void boundHeightByMaxHeightAndOffsetY();

private:
	void setupConnections();
	void defineBounds();
	void addParameters();

private:
	NumericalParameter m_maximumWidth;
	NumericalParameter m_maximumHeight;
	NumericalParameter m_offsetX;
	NumericalParameter m_offsetY;
	ListParameter<QString> m_formats;
	NumericalParameter m_exposureTime;
	NumericalParameter m_gainDB;
};
