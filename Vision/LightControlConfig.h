#pragma once
#include "Config.h"
#include "NumericalParameter.h"
#include "StringParameter.h"

#include <QString>

class LightControlConfig : public Config
{
	Q_OBJECT

public:
	explicit LightControlConfig(QObject* parent = nullptr);
	LightControlConfig(const QString& comPort, int relay, QObject* parent = nullptr);
	LightControlConfig(const LightControlConfig& config, QObject* parent = nullptr);
	~LightControlConfig() override = default;

	QString getComPort() const;
	int getRelay() const;

	void setComPort(const QString& comPort);
	void setRelay(const int relay);

private:
	bool setFromConfig(const Config* src) override;

private:
	void defineBounds();
	void addParameters();

private:
	StringParameter m_comPort;
	NumericalParameter m_relay;
};

