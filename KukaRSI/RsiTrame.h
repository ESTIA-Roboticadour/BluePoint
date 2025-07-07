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
	bool m_isCartesian;
	bool m_isInRobotBase;
	double m_pos[6];
	QString m_ipoc;
	ushort m_digout;
};
