#ifndef NUMERICALPARAMETERWIDGET_H
#define NUMERICALPARAMETERWIDGET_H

#include "NumericalParameter.h"
#include "ParametersWidgetCollection_global.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QSlider>
#include <QDoubleSpinBox>

class PARAMETERS_WIDGETS_API NumericalParameterWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString getName READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(int minimum READ getMinimum WRITE setMinimum NOTIFY minimumChanged)
	Q_PROPERTY(int maximum READ getMaximum WRITE setMaximum NOTIFY maximumChanged)
	Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(int increment READ getIncrement WRITE setIncrement NOTIFY incrementChanged)

public:
	explicit NumericalParameterWidget(QWidget* parent = nullptr);
	~NumericalParameterWidget() = default;

	QString getName() const;
	double getMinimum() const;
	double getMaximum() const;
	double getValue() const;
	double getIncrement() const;

	void setFrom(const NumericalParameter* boolParameter);

public slots:
	void setName(const QString& newName);
	void setMinimum(double min);
	void setMaximum(double max);
	void setValue(double val);
	void setIncrement(double increment);

	void increment();
	void decrement();

private slots:
	void onSliderValueChanged(int value);
	void onSpinBoxValueChanged(double value);

signals:
	void nameChanged(const QString& name);
	void minimumChanged(double minimum);
	void maximumChanged(double maximum);
	void valueChanged(double newValue);
	void incrementChanged(double increment);

private:
	QLabel* m_label;
	QSlider* m_slider;
	QDoubleSpinBox* m_doubleSpinBox;
	QString m_name;
	double m_minValue;
	double m_maxValue;
	double m_increment;
	bool m_isSliderUpdating;
};

#endif // NUMERICALPARAMETERWIDGET_H
