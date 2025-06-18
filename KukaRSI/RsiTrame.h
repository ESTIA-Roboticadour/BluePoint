#pragma once
#include "Trame.h"

class RsiTrame : public Trame
{
public:
	RsiTrame();

	void reset();

	void setPose(bool isCartesian, double pos[6], bool isInRobotBase);
	void setIPOC(const QString& ipoc);

	// Inherited via Trame
	bool isValid() const override;
	QString build() const override;
	Type type() const override 
	{
		return Trame::Type::RSI;
	}

private:
	bool m_isCartesian;
	bool m_isInRobotBase;
	double m_pos[6];
	QString m_ipoc;
};
