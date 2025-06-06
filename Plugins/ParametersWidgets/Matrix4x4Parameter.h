#ifndef MATRIX4X4PARAMETER_H
#define MATRIX4X4PARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QMatrix4x4>
#include <QVector3D>
#include <QJsonObject>

class PARAMETERS_WIDGETS_API Matrix4x4Parameter : public ParameterBase
{
    Q_OBJECT

public:
    explicit Matrix4x4Parameter(const QString& name, const QMatrix4x4& value = QMatrix4x4(), QObject* parent = nullptr);
    Matrix4x4Parameter(const Matrix4x4Parameter& other, QObject* parent = nullptr);
    Matrix4x4Parameter(const QString& name, const Matrix4x4Parameter& other, QObject* parent = nullptr);
    ~Matrix4x4Parameter() = default;

    ParameterBase* copy(QObject* parent = nullptr) const override;

    QMatrix4x4 getMatrix() const;
    QMatrix4x4 getRotationMatrix() const;
    QVector3D  getTranslation() const;

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

public slots:
    void setMatrix(const QMatrix4x4& matrix);
    void setRotationMatrix(const QMatrix4x4& rotation);
    void setTranslation(const QVector3D& translation);

signals:
    void matrixChanged(const QMatrix4x4& matrix);
    void rotationChanged(const QMatrix4x4& rotation);
    void translationChanged(const QVector3D& translation);

private:
    void emitIfChanged(const QMatrix4x4& newMatrix);

private:
    QMatrix4x4 m_matrix;
};

#endif // MATRIX4X4PARAMETER_H
