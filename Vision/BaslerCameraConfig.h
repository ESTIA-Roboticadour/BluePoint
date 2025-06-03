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

	QString getSelectedFormat() const;
	QStringList getFormats() const;

	int getExposureTime() const;
	int getGainDB() const;

	void reset() override;
	Config* copy(QObject* parent = nullptr) override;

protected:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void defineBounds();
	void addParameters();

private:
	ListParameter<QString> m_formats;
	NumericalParameter m_exposureTime;
	NumericalParameter m_gainDB;
};
