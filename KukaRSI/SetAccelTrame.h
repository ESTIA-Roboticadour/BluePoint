#pragma once
#include "Trame.h"
#include <QString>

class SetAccelerationTrame : public Trame
{
public:
    explicit SetAccelerationTrame(double acceleration);

    void setAcceleration(double acceleration);

    // Inherited via Trame
    bool isValid() const override;
    QString build() const override;
    Type type() const override
    {
        return Type::SetAcceleration;
    }

private:
    double m_acceleration;
};
