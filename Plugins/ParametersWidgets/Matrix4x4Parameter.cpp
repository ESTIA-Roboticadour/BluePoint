#include "Matrix4x4Parameter.h"
#include <QJsonArray>

Matrix4x4Parameter::Matrix4x4Parameter(const QString& name, const QMatrix4x4& value, QObject* parent) :
    ParameterBase(name, parent),
    m_matrix(value)
{
}

Matrix4x4Parameter::Matrix4x4Parameter(const Matrix4x4Parameter& other, QObject* parent) :
    ParameterBase(other.getName(), parent),
    m_matrix(other.m_matrix)
{
}

Matrix4x4Parameter::Matrix4x4Parameter(const QString& name, const Matrix4x4Parameter& other, QObject* parent) :
    ParameterBase(name, parent),
    m_matrix(other.m_matrix)
{
}

ParameterBase* Matrix4x4Parameter::copy(QObject* parent) const
{
    return new Matrix4x4Parameter(*this, parent);
}

QMatrix4x4 Matrix4x4Parameter::getMatrix() const
{
    return m_matrix;
}

QMatrix4x4 Matrix4x4Parameter::getRotationMatrix() const
{
    QMatrix4x4 rotation;
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            rotation(row, col) = m_matrix(row, col);
    return rotation;
}

QVector3D Matrix4x4Parameter::getTranslation() const
{
    return { m_matrix(0, 3), m_matrix(1, 3), m_matrix(2, 3) };
}

void Matrix4x4Parameter::setMatrix(const QMatrix4x4& matrix)
{
    if (getIsEditable() && m_matrix != matrix)
        emitIfChanged(matrix);
}

void Matrix4x4Parameter::setRotationMatrix(const QMatrix4x4& rotation)
{
    if (!getIsEditable())
        return;

    QMatrix4x4 newMatrix = m_matrix;
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            newMatrix(row, col) = rotation(row, col);

    emitIfChanged(newMatrix);
}

void Matrix4x4Parameter::setTranslation(const QVector3D& translation)
{
    if (!getIsEditable())
        return;

    QMatrix4x4 newMatrix = m_matrix;
    newMatrix(0, 3) = translation.x();
    newMatrix(1, 3) = translation.y();
    newMatrix(2, 3) = translation.z();

    emitIfChanged(newMatrix);
}

void Matrix4x4Parameter::emitIfChanged(const QMatrix4x4& newMatrix)
{
    if (m_matrix != newMatrix) {
        QMatrix4x4 oldRotation = getRotationMatrix();
        QVector3D  oldTranslation = getTranslation();

        m_matrix = newMatrix;

        emit matrixChanged(m_matrix);
        emit parameterChanged(this);

        if (getRotationMatrix() != oldRotation)
            emit rotationChanged(getRotationMatrix());

        if (getTranslation() != oldTranslation)
            emit translationChanged(getTranslation());
    }
}

QJsonObject Matrix4x4Parameter::toJson() const
{
    QJsonArray matrixArray;
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            matrixArray.append(m_matrix(row, col));

    return {
        {"type", "matrix4x4"},
        {"name", getName()},
        {"matrix", matrixArray}
    };
}

std::unique_ptr<ParameterBase> Matrix4x4Parameter::fromJson(const QJsonObject& obj, QObject* parent)
{
    QJsonArray array = obj["matrix"].toArray();
    QMatrix4x4 mat;
    for (int i = 0; i < 16 && i < array.size(); ++i)
        mat(i / 4, i % 4) = array[i].toDouble();

    return std::make_unique<Matrix4x4Parameter>(obj["name"].toString(), mat, parent);
}
