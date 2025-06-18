#pragma once
#include "Trame.h"

class RsiTrame : public Trame
{
public:
	RsiTrame();

	void reset();

	void setPose(double pos[6]);
	void setIPOC(const QString& ipoc);

	// Inherited via Trame
	bool isValid() const override;
	QString build() const override;
	Type type() const override 
	{
		return Trame::Type::RSI;
	}

private:
	double m_pos[6];
	QString m_ipoc;
};
