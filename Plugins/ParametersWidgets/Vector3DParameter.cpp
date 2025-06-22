#include "Vector3DParameter.h"
#include <QJsonValue>

Vector3DParameter::Vector3DParameter(const QString& name, bool canBeNormalized, QObject* parent) :
    ParameterBase(name, parent),
    m_canBeNormalized(canBeNormalized),
    m_x(0.0), 
    m_y(0.0),
    m_z(0.0)
{
}

Vector3DParameter::Vector3DParameter(const Vector3DParameter& parameter, QObject* parent) :
    ParameterBase(parameter.getName(), parent),
    m_x(parameter.m_x),
    m_y(parameter.m_y),
    m_z(parameter.m_z)
{
}

Vector3DParameter::Vector3DParameter(const QString& name, const Vector3DParameter& parameter, QObject* parent) :
    ParameterBase(name, parent),
    m_x(parameter.m_x),
    m_y(parameter.m_y),
    m_z(parameter.m_z)
{
}

ParameterBase* Vector3DParameter::copy(QObject* parent) const
{
    return new Vector3DParameter(*this, parent);
}

void Vector3DParameter::setX(double x)
{
    if (getIsEditable() && m_x != x)
    {
        m_x = x;
        emit xChanged(x);
        emit parameterChanged(this);
    }
}

void Vector3DParameter::setY(double y)
{
    if (getIsEditable() && m_y != y)
    {
        m_y = y;
        emit yChanged(y);
        emit parameterChanged(this);
    }
}

void Vector3DParameter::setZ(double z)
{
    if (getIsEditable() && m_z != z)
    {
        m_z = z;
        emit zChanged(z);
        emit parameterChanged(this);
    }
}

void Vector3DParameter::setCanBeNormalized(bool canBeNormalized)
{
    if (getIsEditable() && m_canBeNormalized != canBeNormalized)
    {
        m_canBeNormalized = canBeNormalized;
        emit canBeNormalizedChanged(m_canBeNormalized);
        emit parameterChanged(this);
    }
}

void Vector3DParameter::setPosition(const QVector3D& position)
{
    setX(position.x());
    setY(position.y());
    setZ(position.z());
}

void Vector3DParameter::setPosition(double x, double y, double z)
{
    setX(x);
    setY(y);
    setZ(z);
}

void Vector3DParameter::normalized()
{
    QVector3D vecNormalized = getPosition().normalized();
    setX(vecNormalized.x());
    setY(vecNormalized.y());
    setZ(vecNormalized.z());
}

QJsonObject Vector3DParameter::toJson() const
{
    return {
        {"type", "vector3D"},
        {"name", getName()},
        {"canBeNormalized", m_canBeNormalized},
        {"x", m_x},
        {"y", m_y},
        {"z", m_z},
    };
}

std::unique_ptr<ParameterBase> Vector3DParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    auto param = std::make_unique<Vector3DParameter>(
        o["name"].toString(),
        o["canBeNormalized"].toBool(),
        parent);
    param->setX(o["x"].toDouble());
    param->setY(o["y"].toDouble());
    param->setZ(o["z"].toDouble());
    return param;
}
