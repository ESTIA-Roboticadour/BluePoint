#pragma once
#include "Trame.h"

class RsiTrame : public Trame
{
public:
	RsiTrame();

	void reset();

	void setPose(bool isCartesian, double pos[6], bool isInRobotBase);
	void setIPOC(const QString& ipoc);

	ushort getOutputs();
	void setOutputs(bool outputs[16]);

	void setChangeMode(bool changeMode);
	void setMode(ushort mode);
	void setVelocity(double velocity);
	void setAcceleration(double acceleration);

	// Inherited via Trame
	bool isValid() const override;
	QString build() const override;
	Type type() const override 
	{
		return Trame::Type::RSI;
	}

private:
	void encodeBoolArrayToShort(bool io[16], ushort& nIO);

private:
	bool m_changeMode;
	bool m_isCartesian;
	bool m_isInRobotBase;
	ushort m_digout;
	ushort m_mode;
	double m_pos[6];
	QString m_ipoc;
	double m_velocity;
	double m_acceleration;
};
