#ifndef VECTOR3DPARAMETER_H
#define VECTOR3DPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QJsonObject>
#include <QString>
#include <QVector3D>

#include <memory>

class PARAMETERS_WIDGETS_API Vector3DParameter : public ParameterBase
{
    Q_OBJECT

public:
    explicit Vector3DParameter(const QString& name, bool canBeNormalized = true, QObject* parent = nullptr);

    Vector3DParameter(const Vector3DParameter& parameter, QObject* parent = nullptr);
    Vector3DParameter(const QString& name, const Vector3DParameter& parameter, QObject* parent = nullptr);
    ~Vector3DParameter() = default;

    ParameterBase* copy(QObject* parent = nullptr) const override;

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

    // Getters
    bool   getCanBeNormalized() const { return m_canBeNormalized; }
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }

    QVector3D getPosition() const  { return QVector3D(m_x, m_y, m_z); }

public slots:
    // Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setCanBeNormalized(bool canBeNormalized);

    void setPosition(const QVector3D& position);
    void setPosition(double x, double y, double z);

    void normalized();

signals:
    void canBeNormalizedChanged(bool canBeNormalized);
    void xChanged(double x);
    void yChanged(double y);
    void zChanged(double z);

private:
    bool m_canBeNormalized;
    double m_x;
    double m_y;
    double m_z;
};

#endif // VECTOR3DPARAMETER_H
