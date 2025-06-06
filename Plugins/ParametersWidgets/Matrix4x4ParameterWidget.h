#ifndef MATRIX4X4PARAMETERWIDGET_H
#define MATRIX4X4PARAMETERWIDGET_H

#include "ParametersWidgetCollection_global.h"
#include "ParameterWidget.h"
#include "Matrix4x4Parameter.h"

#include <QWidget>
#include <QMatrix4x4>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QVector>
#include <QString>

class PARAMETERS_WIDGETS_API Matrix4x4ParameterWidget : public ParameterWidget
{
    Q_OBJECT
    Q_PROPERTY(QMatrix4x4 matrix READ getMatrix WRITE setMatrix NOTIFY matrixChanged)

public:
    explicit Matrix4x4ParameterWidget(bool readOnly = false, QWidget* parent = nullptr);
    ~Matrix4x4ParameterWidget() override = default;

    QString getName() const;
    QMatrix4x4 getMatrix() const;
    int getLabelWidth() const override;

public slots:
    void setName(const QString& newName);
    void setMatrix(const QMatrix4x4& matrix);
    void setRotationMatrix(const QMatrix4x4& rotation);
    void setTranslation(const QVector3D& translation);
    void setLabelWidth(int width) override;
    void setFrom(const Matrix4x4Parameter* matrix4x4Parameter);
    void setEnabled(bool enabled);

private slots:
    void onLineEditEdited();

private:
    void setupUI();
    void updateUIFromMatrix(const QMatrix4x4& matrix);

signals:
    void nameChanged(const QString& name);
    void matrixChanged(const QMatrix4x4& matrix);

private:
    QString m_name;
    QMatrix4x4 m_matrix;
    bool m_readOnly;
    QVector<QLineEdit*> m_lineEdits;
    QLabel* m_label;
    QGridLayout* m_layout;
};

#endif // MATRIX4X4PARAMETERWIDGET_H
