#ifndef NUMERICALPARAMETER_H
#define NUMERICALPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>

class PARAMETERS_WIDGETS_API NumericalParameter : public ParameterBase
{
	Q_OBJECT

public:
	explicit NumericalParameter(const QString& name, const double value=50., QObject* parent = nullptr);
	~NumericalParameter() = default;

	double getValue() const;
	double getMinimum() const;
	double getMaximum() const;
	int	   getIncrement() const;

public slots:
	void setValue(double value);
	void setMinimum(double minimum);
	void setMaximum(double maximum);
	void setIncrement(double increment);

	void increment();
	void decrement();

private:
	void internalSetValue(double value);

signals:
	void valueChanged(double value);
	void minimumChanged(double minimum);
	void maximumChanged(double maximum);
	void incrementChanged(double increment);

private:
	double m_value;
	double m_minimum;
	double m_maximum;
	double m_increment;
};

#endif // NUMERICALPARAMETER_H
