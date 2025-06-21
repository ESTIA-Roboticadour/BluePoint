#ifndef EULERFRAMEPARAMETER_H
#define EULERFRAMEPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QJsonObject>
#include <QString>
#include <QVector3D>
#include <QList>
#include <QMatrix3x3>

#include <cmath>
#include <memory>

class PARAMETERS_WIDGETS_API EulerFrameParameter : public ParameterBase
{
    Q_OBJECT

public:
    enum Convention {
        XYX, XZX, YXY, YZY, ZXZ, ZYZ, // Proper Euler
        XYZ, XZY, YXZ, YZX, ZXY, ZYX, // Tait–Bryan
    };
    Q_ENUM(Convention)

    inline static QString toQString(Convention convention) {
        switch (convention) {
            // Proper Euler
        case Convention::XYX: return "XYX";
        case Convention::XZX: return "XZX";
        case Convention::YXY: return "YXY";
        case Convention::YZY: return "YZY";
        case Convention::ZXZ: return "ZXZ";
        case Convention::ZYZ: return "ZYZ";
            // Tait–Bryan
        case Convention::XYZ: return "XYZ";
        case Convention::XZY: return "XZY";
        case Convention::YXZ: return "YXZ";
        case Convention::YZX: return "YZX";
        case Convention::ZXY: return "ZXY";
        case Convention::ZYX: return "ZYX";
        default: return "";
        }
    }

    explicit EulerFrameParameter(const QString& name,
                                 Convention convention = Convention::XYZ,
                                 QObject* parent = nullptr);

    EulerFrameParameter(const EulerFrameParameter& parameter, QObject* parent = nullptr);
    EulerFrameParameter(const QString& name, const EulerFrameParameter& parameter, QObject* parent = nullptr);
    ~EulerFrameParameter() = default;

    ParameterBase* copy(QObject* parent = nullptr) const override;

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

    // Getters
    Convention getConvention() const;
    double getX() const;
    double getY() const;
    double getZ() const;
    double getA() const;
    double getB() const;
    double getC() const;

    QString conventionString() const;
    QVector3D getPosition() const;
    QVector3D getAngles() const;

    QMatrix3x3 toMatrix() const;
    void fromMatrix(const QMatrix3x3& matrix);

    static QList<EulerFrameParameter::Convention> getConventions();

public slots:
    // Setters
    void setConvention(Convention convention);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    // set 1st rotation angle in degrees
    void setA(double a);
    // set 2nd rotation angle in degrees
    void setB(double b);
    // set 3rd rotation angle in degrees
    void setC(double c);

    void setPosition(const QVector3D& position);
    void setPosition(double x, double y, double z);
    void setAngles(const QVector3D& angles);
    void setAngles(double a, double b, double c);
    void setEulerFrame(const QVector3D& position, const QVector3D& angles);
    void setEulerFrame(double x, double y, double z, double a, double b, double c);

private:
    inline static double clampAngle(double deg) {
        if (deg < -180.0) return -180.0;
        if (deg > 180.0) return 180.0;
        return deg;
    }

    inline static QMatrix3x3 makeMatrix(
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22)
    {
        QMatrix3x3 mat;
        mat(0,0) = m00; mat(0,1) = m01; mat(0,2) = m02;
        mat(1,0) = m10; mat(1,1) = m11; mat(1,2) = m12;
        mat(2,0) = m20; mat(2,1) = m21; mat(2,2) = m22;
        return mat;
    }

    inline static double safeAcos(double x) { return std::acos(std::clamp(x, -1.0, 1.0)); }
    inline static double safeAsin(double x) { return std::asin(std::clamp(x, -1.0, 1.0)); }
    inline static double toRadians(double degrees) { return degrees * M_PI / 180.0; }
    inline static double toDegrees(double radians) { return radians * 180.0 / M_PI; }

signals:
    void conventionChanged(Convention convention);
    void xChanged(double x);
    void yChanged(double y);
    void zChanged(double z);
    void aChanged(double a);
    void bChanged(double b);
    void cChanged(double c);

private:
    Convention m_convention;
    double m_x, m_y, m_z;
    double m_a, m_b, m_c;
};

#endif // EULERFRAMEPARAMETER_H
