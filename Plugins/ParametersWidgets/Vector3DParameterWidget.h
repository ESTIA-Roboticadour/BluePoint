#ifndef VECTOR3DPARAMETERWIDGET_H
#define VECTOR3DPARAMETERWIDGET_H

#include "Vector3DParameter.h"
#include "ParametersWidgetCollection_global.h"
#include "ParameterWidget.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVector3D>
#include <QVBoxLayout>
#include <QPushButton>

class PARAMETERS_WIDGETS_API Vector3DParameterWidget : public ParameterWidget
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged)
    Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(bool canNormalize READ getCanNormalize WRITE setCanNormalize NOTIFY canNormalizeChanged)

public:
    explicit Vector3DParameterWidget(
        bool readOnly = false,
        bool canNormalize = true,
        QWidget* parent = nullptr);
    ~Vector3DParameterWidget() = default;

    QString getName() const;
    QVector3D getPosition() const;
    double getX() const { return m_posSpin[0]->value(); }
    double getY() const { return m_posSpin[1]->value(); }
    double getZ() const { return m_posSpin[2]->value(); }
    bool getCanNormalize() const { return m_normalizeButton != nullptr; }

    void setFrom(const Vector3DParameter* parameter);
    int getLabelWidth() const override;

public slots:
    void setName(const QString& newName);
    void setPosition(const QVector3D& position);
    void setPosition(double x, double y, double z);
    void setX(double value);
    void setY(double value);
    void setZ(double value);
    void setCanNormalize(bool canNormalize);
    void setLabelWidth(int width) override;
    void setEnabled(bool enabled);

private slots:
    void onNormalizeButtonClicked();

private:
    void createUI();
    void connectSignals();

signals:
    void nameChanged(const QString& name);
    void xChanged(double x);
    void yChanged(double y);
    void zChanged(double z);
    void canNormalizeChanged(bool canNormalize);

private:
    bool m_readOnly;
    QString m_name;
    QLabel* m_label;
    QDoubleSpinBox* m_posSpin[3];
    QVBoxLayout* m_paramsLayout {nullptr};
    QPushButton* m_normalizeButton {nullptr};
};

#endif // VECTOR3DPARAMETERWIDGET_H
