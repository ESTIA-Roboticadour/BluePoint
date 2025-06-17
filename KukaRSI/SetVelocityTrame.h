#pragma once
#include "Trame.h"
#include <QString>

class SetVelocityTrame : public Trame
{
public:
    explicit SetVelocityTrame(double velocity);

    void setVelocity(double velocity);
    
    // Inherited via Trame
    bool isValid() const override;
    QString build() const override;
    Type type() const override 
    {
        return Type::SetVelocity;
    }

private:
    double m_velocity;
};
