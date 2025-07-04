#pragma once
#include "Config.h"
#include "NumericalParameter.h"
#include "ListParameter.h"

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

	void reset() override;
	Config* copy(QObject* parent=nullptr) const override;

private:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void defineBounds();
	void addParameters();

private:
	ListParameter<QString> m_comPort;
	NumericalParameter m_relay;
};
