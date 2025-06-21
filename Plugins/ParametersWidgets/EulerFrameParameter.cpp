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
    // https://en.wikipedia.org/wiki/Euler_angles

    const double a = toRadians(m_a);
    const double b = toRadians(m_b);
    const double c = toRadians(m_c);

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

    // Tait-Bryan
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

void EulerFrameParameter::fromMatrix(const QMatrix3x3 &matrix)
{
    // https://en.wikipedia.org/wiki/Euler_angles

    double R11 = matrix(0, 0);
    double R12 = matrix(0, 1);
    double R13 = matrix(0, 2);
    double R21 = matrix(1, 0);
    double R22 = matrix(1, 1);
    double R23 = matrix(1, 2);
    double R31 = matrix(2, 0);
    double R32 = matrix(2, 1);
    double R33 = matrix(2, 2);

    switch (m_convention)
    {
    // Proper Euler
    case Convention::XYX:
        setA(toDegrees(std::atan2(R21, -R31)));
        setB(toDegrees(safeAcos(R11)));
        setC(toDegrees(std::atan2(R12, R13)));
        break;
    case Convention::XZX:
        setA(toDegrees(std::atan2(R31, R21)));
        setB(toDegrees(safeAcos(R11)));
        setC(toDegrees(std::atan2(R13, -R12)));
        break;
    case Convention::YXY:
        setA(toDegrees(std::atan2(R12, R32)));
        setB(toDegrees(safeAcos(R22)));
        setC(toDegrees(std::atan2(R21, -R23)));
        break;
    case Convention::YZY:
        setA(toDegrees(std::atan2(R32, -R12)));
        setB(toDegrees(safeAcos(R22)));
        setC(toDegrees(std::atan2(R23, R21)));
        break;
    case Convention::ZXZ:
        setA(toDegrees(0.));
        setB(toDegrees(0.));
        setC(toDegrees(0.));
        break;
    case Convention::ZYZ:
        setA(toDegrees(std::atan2(R23, R13)));
        setB(toDegrees(std::atan2(std::sqrt(1 - R33*R33), R33)));
        setC(toDegrees(std::atan2(R31, R32)));
        break;
    // Tait–Bryan
    case Convention::XYZ:
        setA(toDegrees(std::atan2(-R23, R33)));
        setB(toDegrees(safeAsin(R13)));
        setC(toDegrees(std::atan2(-R12, R11)));
        break;
    case Convention::XZY:
        setA(toDegrees(std::atan2(R32, R22)));
        setB(toDegrees(safeAsin(-R12)));
        setC(toDegrees(std::atan2(R13, R11)));
        break;
    case Convention::YXZ:
        setA(toDegrees(std::atan2(R13, R33)));
        setB(toDegrees(safeAsin(-R23)));
        setC(toDegrees(std::atan2(R21, R22)));
        break;
    case Convention::YZX:
        setA(toDegrees(std::atan2(-R31, R11)));
        setB(toDegrees(safeAsin(R21)));
        setC(toDegrees(std::atan2(-R23, R22)));
        break;
    case Convention::ZXY:
        setA(toDegrees(std::atan2(-R12, R22)));
        setB(toDegrees(safeAsin(R32)));
        setC(toDegrees(std::atan2(R32, R33)));
        break;
    case Convention::ZYX:
        setA(toDegrees(std::atan2(R21, R11)));
        setB(toDegrees(safeAsin(-R31)));
        setC(toDegrees(std::atan2(R32, R33)));
        break;
    }
}

QList<EulerFrameParameter::Convention> EulerFrameParameter::getConventions()
{
    return QList({
        XYX, XZX, YXY, YZY, ZXZ, ZYZ, // Proper Euler
        XYZ, XZY, YXZ, YZX, ZXY, ZYX  // Tait–Bryan
    });
}

void EulerFrameParameter::setConvention(Convention convention)
{
    if (getIsEditable() && m_convention != convention)
    {
        QMatrix3x3 matrix = toMatrix();
        m_convention = convention;
        fromMatrix(matrix);

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
