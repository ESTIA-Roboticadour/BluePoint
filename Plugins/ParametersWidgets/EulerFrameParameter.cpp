#include "EulerFrameParameter.h"
#include <QJsonValue>

EulerFrameParameter::EulerFrameParameter(const QString& name,
                                         Convention convention,
                                         QObject* parent) :
    ParameterBase(name, parent),
    m_convention(convention),
    m_x(0.0), m_y(0.0), m_z(0.0),
    m_a(0.0), m_b(0.0), m_c(0.0)
{
}

EulerFrameParameter::EulerFrameParameter(const EulerFrameParameter& parameter, QObject* parent) :
    ParameterBase(parameter.getName(), parent),
    m_convention(parameter.m_convention),
    m_x(parameter.m_x), m_y(parameter.m_y), m_z(parameter.m_z),
    m_a(parameter.m_a), m_b(parameter.m_b), m_c(parameter.m_c)
{
}

EulerFrameParameter::EulerFrameParameter(const QString& name, const EulerFrameParameter& parameter, QObject* parent) :
    ParameterBase(name, parent),
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
    return toQString(m_convention);
}

QVector3D EulerFrameParameter::getPosition() const {
    return QVector3D(m_x, m_y, m_z);
}

QVector3D EulerFrameParameter::getAngles() const {
    return QVector3D(m_a, m_b, m_c);
}

QMatrix3x3 EulerFrameParameter::toMatrix() const {
    const double a = m_a, b = m_b, c = m_c;
    const double ca = std::cos(a), sa = std::sin(a);
    const double cb = std::cos(b), sb = std::sin(b);
    const double cc = std::cos(c), sc = std::sin(c);

    switch (m_convention)
    {
    // Proper Euler
    case Convention::XYX:
        return makeMatrix(
             cb,    sb*sc,             cc*sb,
             sa*sb, ca*cc - cb*sa*sc, -ca*sc - cb*cc*sa,
            -ca*sb, cc*sa + ca*cb*sc,  ca*cb*cc - sa*sc
            );

    case Convention::XZX:
        return makeMatrix(
            cb,    -cc*sb,             sb*sc,
            ca*sb,  ca*cb*cc - sa*sc, -cc*sa - ca*cb*sc,
            sa*sb,  ca*sc + cb*cc*sa,  ca*cc - cb*sa*sc
            );

    case Convention::YXY:
        return makeMatrix(
             ca*cc - cb*sa*sc, sa*sb,  ca*sc + cb*cc*sa,
             sb*sc,            cb,    -cc*sb,
            -cc*sa - ca*cb*sc, ca*sb,  ca*cb*cc - sa*sc
            );

    case Convention::YZY:
        return makeMatrix(
             ca*cb*cc - sa*sc, -ca*sb, cc*sa + ca*cb*sc,
             cc*sb,             cb,    sb*sc,
            -ca*sc - cb*cc*sa,  sa*sb, ca*cc - cb*sa*sc
            );

    case Convention::ZXZ:
        return makeMatrix(
            ca*cc - cb*sa*sc, -ca*sc - cb*cc*sa,  sa*sb,
            cc*sa + ca*cb*sc,  ca*cb*cc - sa*sc, -ca*sb,
            sb*sc,             cc*sb,             cb
            );

    case Convention::ZYZ:
        return makeMatrix(
             ca*cb*cc - sa*sc, -cc*sa - ca*cb*sc, ca*sb,
             ca*sc + cb*cc*sa,  ca*cc - cb*sa*sc, sa*sb,
            -cc*sb,             sb*sc,            cb
            );

    case Convention::XYZ:
        return makeMatrix(
            cb*cc,            -cb*sc,             sb,
            ca*sc + cc*sa*sb,  ca*cc - sa*sb*sc, -cb*sa,
            sa*sc - ca*cc*sb,  cc*sa + ca*sb*sc,  ca*cb
            );

    // Tait–Bryan
    case Convention::XZY:
        return makeMatrix(
            cb*cc,            -sb,    cb*sc,
            sa*sc + ca*cc*sb,  ca*cb, ca*sb*sc - cc*sa,
            cc*sa*sb - ca*sc,  cb*sa, ca*cc + sa*sb*sc
            );

    case Convention::YXZ:
        return makeMatrix(
            ca*cc + sa*sb*sc, cc*sa*sb - ca*sc,  cb*sa,
            cb*sc,            cb*cc,            -sb,
            ca*sb*sc - cc*sa, ca*cc*sb + sa*sc,  ca*cb
            );

    case Convention::YZX:
        return makeMatrix(
             ca*cb, sa*sc - ca*cc*sb,  cc*sa + ca*sb*sc,
             sb,    cb*cc,            -cb*sc,
            -cb*sa, ca*sc + cc*sa*sb,  ca*cc - sa*sb*sc
            );

    case Convention::ZXY:
        return makeMatrix(
             ca*cc - sa*sb*sc, -cb*sa, ca*sc + cc*sa*sb,
             cc*sa + ca*sb*sc,  ca*cb, sa*sc - ca*cc*sb,
            -cb*sc,             sb,    cb*cc
            );

    case Convention::ZYX:
        return makeMatrix(
             ca*cb, ca*sb*sc - cc*sa, sa*sc + ca*cc*sb,
             cb*sa, ca*cc + sa*sb*sc, cc*sa*sb - ca*sc,
            -sb,    cb*sc,            cb*cc
            );

    default:
        return QMatrix3x3(); // Identity
    }
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

void EulerFrameParameter::setEulerFrame(const QVector3D& position, const QVector3D& angles)
{
    setX(position.x());
    setY(position.y());
    setZ(position.z());
    setA(angles.x());
    setB(angles.y());
    setC(angles.z());
}

void EulerFrameParameter::setEulerFrame(double x, double y, double z, double a, double b, double c)
{
    setX(x);
    setY(y);
    setZ(z);
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
