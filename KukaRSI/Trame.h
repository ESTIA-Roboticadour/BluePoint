#pragma once
#include <QString>

class Trame
{
public:
    enum class Type {
        RSI,
        CartesianMovement,
        ArticularMovement,
        SetVelocity,
        SetAcceleration,
        IOCommand
    };

    virtual ~Trame() = default;
    virtual bool isValid() const = 0;
    virtual QString build() const = 0;
    virtual Type type() const = 0;
};
