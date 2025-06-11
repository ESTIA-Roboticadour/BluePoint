#pragma once
#include "Config.h"
#include "StringParameter.h"
#include "NumericalParameter.h"
#include "Matrix4x4Parameter.h"
#include <QMatrix4x4>

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
	QMatrix4x4 getMatrix() const;

	void setAddress(const QString& address);
	void setPort(const int port);
	void setMaxSpeed(const int maxSpeed);
	void setMaxAccel(const int maxAccel);
	void setMatrix(const QMatrix4x4& matrix);

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
	Matrix4x4Parameter m_matrix;
};
