#ifndef EULERFRAMEPARAMETERWIDGET_H
#define EULERFRAMEPARAMETERWIDGET_H

#include "EulerFrameParameter.h"
#include "ParametersWidgetCollection_global.h"
#include "ParameterWidget.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QVector3D>

class PARAMETERS_WIDGETS_API EulerFrameParameterWidget : public ParameterWidget
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(double x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ getY WRITE setY NOTIFY yChanged)
    Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(double a READ getA WRITE setA NOTIFY aChanged)
    Q_PROPERTY(double b READ getB WRITE setB NOTIFY bChanged)
    Q_PROPERTY(double c READ getC WRITE setC NOTIFY cChanged)
    Q_PROPERTY(EulerFrameParameter::Convention convention READ getConvention WRITE setConvention NOTIFY conventionChanged FINAL)

public:
    explicit EulerFrameParameterWidget(
        bool readOnly = false,
        QWidget* parent = nullptr);
    ~EulerFrameParameterWidget() = default;

    QString getName() const;
    EulerFrameParameter::Convention getConvention() const;
    QVector3D getPosition() const;
    QVector3D getAngles() const;
    double getX() const { return m_posSpin[0]->value(); }
    double getY() const { return m_posSpin[1]->value(); }
    double getZ() const { return m_posSpin[2]->value(); }
    double getA() const { return m_angleSpin[0]->value(); }
    double getB() const { return m_angleSpin[1]->value(); }
    double getC() const { return m_angleSpin[2]->value(); }

    void setFrom(const EulerFrameParameter* parameter);
    int getLabelWidth() const override;

public slots:
    void setName(const QString& newName);
    void setConvention(EulerFrameParameter::Convention convention);
    void setPosition(const QVector3D& position);
    void setAngles(const QVector3D& angles);
    void setX(double value);
    void setY(double value);
    void setZ(double value);
    void setA(double value);
    void setB(double value);
    void setC(double value);
    void setLabelWidth(int width) override;
    void setEnabled(bool enabled);

private slots:
    void onConventionChanged(int selectedIndex);
    void onSliderValueChanged(int index, int value);
    void onSpinBoxValueChanged(int index, double value);

private:
    void createUI();
    void connectSignals();

signals:
    void nameChanged(const QString& name);
    void conventionChanged(EulerFrameParameter::Convention convention);
    void xChanged(double x);
    void yChanged(double y);
    void zChanged(double z);
    void aChanged(double a);
    void bChanged(double b);
    void cChanged(double c);

private:
    bool m_readOnly;
    EulerFrameParameter::Convention m_convention;
    QString m_name;
    QLabel* m_label;
    QComboBox* m_comboBox;
    QDoubleSpinBox* m_posSpin[3];
    QDoubleSpinBox* m_angleSpin[3];
    QSlider* m_angleSlider[3];
    bool m_isSliderUpdating;
};

#endif // EULERFRAMEPARAMETERWIDGET_H
