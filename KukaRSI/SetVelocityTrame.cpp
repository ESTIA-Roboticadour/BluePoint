#include "SetVelocityTrame.h"

SetVelocityTrame::SetVelocityTrame(double velocity) :
	m_velocity(0.)
{
	setVelocity(velocity);
}

void SetVelocityTrame::setVelocity(double velocity)
{
	if (velocity != m_velocity)
		m_velocity = velocity;
}

bool SetVelocityTrame::isValid() const
{
	return m_velocity >= 0. && m_velocity <= 100.;
}

QString SetVelocityTrame::build() const
{
	return QString("S_V %1").arg(m_velocity);
}
