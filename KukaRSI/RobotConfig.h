#pragma once
#include "Config.h"
#include "StringParameter.h"
#include "NumericalParameter.h"
#include "EulerFrameParameter.h"

class RobotConfig : public Config
{
	Q_OBJECT

public:
	explicit RobotConfig(QObject* parent = nullptr);
	RobotConfig(const RobotConfig& config, QObject* parent = nullptr);
	~RobotConfig() override = default;

	QString getAddress() const;
	int getPort() const;
	int getMaxSpeed() const;
	int getMaxAccel() const;
	const EulerFrameParameter* getTool() const;

	void setAddress(const QString& address);
	void setPort(const int port);
	void setMaxSpeed(const int maxSpeed);
	void setMaxAccel(const int maxAccel);

	void reset() override;
	Config* copy(QObject* parent = nullptr) const override;

protected:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void defineBounds();
	void addParameters();

private:
	StringParameter	   m_address;
	NumericalParameter m_port;
	NumericalParameter m_maxSpeed;
	NumericalParameter m_maxAccel;
	EulerFrameParameter m_toolParameter;
};
