#include "SetAccelTrame.h"

SetAccelerationTrame::SetAccelerationTrame(double acceleration) :
	m_acceleration(0.)
{
	setAcceleration(acceleration);
}

void SetAccelerationTrame::setAcceleration(double acceleration)
{
	if (acceleration != m_acceleration)
		m_acceleration = acceleration;
}

bool SetAccelerationTrame::isValid() const
{
	return m_acceleration >= 0. && m_acceleration <= 100.;
}

QString SetAccelerationTrame::build() const
{
	return QString("SET_ACC %1").arg(m_acceleration);
}
