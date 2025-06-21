#ifndef EULERFRAMEPARAMETER_H
#define EULERFRAMEPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QJsonObject>
#include <QString>
#include <QVector3D>
#include <QList>
#include <memory>
//#include <QMatrix3x3>

class PARAMETERS_WIDGETS_API EulerFrameParameter : public ParameterBase
{
    Q_OBJECT

public:
    enum Convention {
        XYZ, YZX, ZXY, XZY, ZYX, YXZ,  // Tait–Bryan
        ZXZ, XYX, YZY, ZYZ, XZX, YXY   // Proper Euler
    };
    Q_ENUM(Convention)

    inline static QString toQString(Convention convention) {
        switch (convention) {
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

    //QMatrix3x3 toMatrix() const;
    //void fromMatrix(const QMatrix3x3& matrix) const;

    static QList<EulerFrameParameter::Convention> getConventions();

public slots:
    // Setters
    void setConvention(Convention convention);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setA(double a);
    void setB(double b);
    void setC(double c);

    void setPosition(const QVector3D& position);
    void setPosition(double x, double y, double z);
    void setAngles(const QVector3D& angles);
    void setAngles(double a, double b, double c);
    void setEulerFrame(const QVector3D& position, const QVector3D& angles);
    void setEulerFrame(double x, double y, double z, double a, double b, double c);

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
