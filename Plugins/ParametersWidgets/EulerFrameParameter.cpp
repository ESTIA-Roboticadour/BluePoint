#include "EulerFrameParameter.h"
#include <QJsonValue>

static double clampAngle(double deg) {
    if (deg < -180.0) return -180.0;
    if (deg > 180.0) return 180.0;
    return deg;
}

EulerFrameParameter::EulerFrameParameter(const QString& name,
                                         Convention convention,
                                         QObject* parent)
    : ParameterBase(name, parent),
    m_convention(convention),
    m_x(0.0), m_y(0.0), m_z(0.0),
    m_a(0.0), m_b(0.0), m_c(0.0)
{
}

EulerFrameParameter::EulerFrameParameter(const EulerFrameParameter& parameter, QObject* parent)
    : ParameterBase(parameter.getName(), parent),
    m_convention(parameter.m_convention),
    m_x(parameter.m_x), m_y(parameter.m_y), m_z(parameter.m_z),
    m_a(parameter.m_a), m_b(parameter.m_b), m_c(parameter.m_c)
{
}

EulerFrameParameter::EulerFrameParameter(const QString& name, const EulerFrameParameter& parameter, QObject* parent)
    : ParameterBase(name, parent),
    m_convention(parameter.m_convention),
    m_x(parameter.m_x), m_y(parameter.m_y), m_z(parameter.m_z),
    m_a(parameter.m_a), m_b(parameter.m_b), m_c(parameter.m_c)
{
}

ParameterBase* EulerFrameParameter::copy(QObject* parent) const
{
    return new EulerFrameParameter(*this, parent);
}

EulerFrameParameter::Convention EulerFrameParameter::getConvention() const { return m_convention; }
double EulerFrameParameter::getX() const { return m_x; }
double EulerFrameParameter::getY() const { return m_y; }
double EulerFrameParameter::getZ() const { return m_z; }
double EulerFrameParameter::getA() const { return m_a; }
double EulerFrameParameter::getB() const { return m_b; }
double EulerFrameParameter::getC() const { return m_c; }

QString EulerFrameParameter::conventionString() const {
    switch (m_convention) {
    case Convention::XYZ: return "XYZ";
    case Convention::YZX: return "YZX";
    case Convention::ZXY: return "ZXY";
    case Convention::XZY: return "XZY";
    case Convention::ZYX: return "ZYX";
    case Convention::YXZ: return "YXZ";
    case Convention::ZXZ: return "ZXZ";
    case Convention::XYX: return "XYX";
    case Convention::YZY: return "YZY";
    case Convention::ZYZ: return "ZYZ";
    case Convention::XZX: return "XZX";
    case Convention::YXY: return "YXY";
    default: return "Unknown";
    }
}

QVector3D EulerFrameParameter::getPosition() const {
    return QVector3D(m_x, m_y, m_z);
}

QVector3D EulerFrameParameter::getAngles() const {
    return QVector3D(m_a, m_b, m_c);
}

QList<EulerFrameParameter::Convention> EulerFrameParameter::getConventions()
{
    return QList({
        Convention::XYZ,
        Convention::YZX,
        Convention::ZXY,
        Convention::XZY,
        Convention::ZYX,
        Convention::YXZ,
        Convention::ZXZ,
        Convention::XYX,
        Convention::YZY,
        Convention::ZYZ,
        Convention::XZX,
        Convention::YXY
    }) ;
}

void EulerFrameParameter::setConvention(Convention convention)
{
    if (getIsEditable() && m_convention != convention)
    {
        m_convention = convention;
        // @TODO : mettre a jour les angles selon la nouvelle convention (toMatrix, fromMatrix)
        emit conventionChanged(m_convention);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setX(double x)
{
    if (getIsEditable() && m_x != x)
    {
        m_x = x;
        emit xChanged(x);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setY(double y)
{
    if (getIsEditable() && m_y != y)
    {
        m_y = y;
        emit yChanged(y);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setZ(double z)
{
    if (getIsEditable() && m_z != z)
    {
        m_z = z;
        emit zChanged(z);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setA(double a)
{
    double clamped = clampAngle(a);
    if (getIsEditable() && m_a != clamped)
    {
        m_a = clamped;
        emit aChanged(clamped);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setB(double b)
{
    double clamped = clampAngle(b);
    if (getIsEditable() && m_b != clamped)
    {
        m_b = clamped;
        emit bChanged(clamped);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setC(double c)
{
    double clamped = clampAngle(c);
    if (getIsEditable() && m_c != clamped)
    {
        m_c = clamped;
        emit cChanged(clamped);
        emit parameterChanged(this);
    }
}

void EulerFrameParameter::setPosition(const QVector3D& position)
{
    setX(position.x());
    setY(position.y());
    setZ(position.z());
}

void EulerFrameParameter::setPosition(double x, double y, double z)
{
    setX(x);
    setY(y);
    setZ(z);
}

void EulerFrameParameter::setAngles(const QVector3D& angles)
{
    setA(angles.x());
    setB(angles.y());
    setC(angles.z());
}

void EulerFrameParameter::setAngles(double a, double b, double c)
{
    setA(a);
    setB(b);
    setC(c);
}

QJsonObject EulerFrameParameter::toJson() const
{
    return {
        {"type", "eulerFrame"},
        {"name", getName()},
        {"convention", static_cast<int>(m_convention)},
        {"x", m_x},
        {"y", m_y},
        {"z", m_z},
        {"a", m_a},
        {"b", m_b},
        {"c", m_c}
    };
}

std::unique_ptr<ParameterBase> EulerFrameParameter::fromJson(const QJsonObject& o, QObject* parent)
{
    auto param = std::make_unique<EulerFrameParameter>(
        o["name"].toString(),
        static_cast<Convention>(o["convention"].toInt()),
        parent);

    param->setX(o["x"].toDouble());
    param->setY(o["y"].toDouble());
    param->setZ(o["z"].toDouble());
    param->setA(o["a"].toDouble());
    param->setB(o["b"].toDouble());
    param->setC(o["c"].toDouble());

    return param;
}
