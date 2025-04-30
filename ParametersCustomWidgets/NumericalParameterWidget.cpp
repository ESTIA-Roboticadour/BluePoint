#include "NumericalParameterWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

NumericalParameterWidget::NumericalParameterWidget(QWidget* parent) :
	QWidget(parent),
	m_minValue(0),
	m_maxValue(100),
	m_increment(1.),
	m_isSliderUpdating(false),
	m_name("Numerical Parameter"),
	m_label(new QLabel("Numerical Parameter:", this)),
	m_slider(new QSlider(Qt::Horizontal, this)),
	m_doubleSpinBox(new QDoubleSpinBox(this))
{
	m_slider->setRange(m_minValue, m_maxValue);
	m_slider->setSingleStep(m_increment);
	m_doubleSpinBox->setRange(m_minValue, m_maxValue);
	m_doubleSpinBox->setSingleStep(m_increment);

	QHBoxLayout* layoutControls = new QHBoxLayout;
	layoutControls->addWidget(m_slider);
	layoutControls->addWidget(m_doubleSpinBox);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_label);
	mainLayout->addLayout(layoutControls);

	connect(m_slider, &QSlider::valueChanged, this, &NumericalParameterWidget::onSliderValueChanged);
	connect(m_doubleSpinBox, &QDoubleSpinBox::valueChanged, this, &NumericalParameterWidget::onSpinBoxValueChanged);

	connect(m_doubleSpinBox, &QDoubleSpinBox::valueChanged, this, &NumericalParameterWidget::valueChanged);
}

QString NumericalParameterWidget::getName() const { return m_name; }

void NumericalParameterWidget::setName(const QString& newName)
{
	if (m_name != newName)
	{
		m_name = newName;
		m_label->setText(m_name + ':');
		emit nameChanged(newName);
	}
}

double NumericalParameterWidget::getMinimum() const { return m_minValue; }

void NumericalParameterWidget::setMinimum(double min)
{
	if (m_minValue != min && min > m_maxValue)
	{
		m_minValue = min;
		m_slider->setMinimum(min);
		m_doubleSpinBox->setMinimum(min);
		emit minimumChanged(min);

		if (getValue() < m_minValue)
		{
			setValue(m_minValue);
		}
	}
}

double NumericalParameterWidget::getMaximum() const { return m_maxValue; }

void NumericalParameterWidget::setMaximum(double max)
{
	if (m_maxValue != max && max > m_minValue)
	{
		m_maxValue = max;
		m_slider->setMaximum(max);
		m_doubleSpinBox->setMaximum(max);
		emit maximumChanged(max);

		if (getValue() > m_maxValue)
		{
			setValue(m_maxValue);
		}
	}
}

double NumericalParameterWidget::getValue() const { return m_doubleSpinBox->value(); }

void NumericalParameterWidget::setValue(double val) { m_doubleSpinBox->setValue(val); }

void NumericalParameterWidget::setIncrement(double increment)
{
	if (increment > 0. && m_increment != increment)
	{
		m_increment = increment;
		m_slider->setSingleStep(round(increment));
		m_doubleSpinBox->setSingleStep(increment);
		emit incrementChanged(increment);
	}
}

double NumericalParameterWidget::getIncrement() const { return m_increment; }

void NumericalParameterWidget::setFrom(const NumericalParameter* parameter)
{
	setName(parameter->getName());
	setMinimum(parameter->getMinimum());
	setMaximum(parameter->getMaximum());
	setIncrement(parameter->getIncrement());
	setValue(parameter->getValue());
	setEnabled(parameter->getIsEditable());
}

void NumericalParameterWidget::onSpinBoxValueChanged(double value)
{
    m_isSliderUpdating = true;
	m_slider->setValue(value);
	m_isSliderUpdating = false;
}

void NumericalParameterWidget::onSliderValueChanged(int value)
{
	if (!m_isSliderUpdating)
	{
		m_doubleSpinBox->setValue(value);
	}
}

void NumericalParameterWidget::increment()
{
	double newValue = m_slider->value() + m_increment;
	m_slider->setValue(newValue < m_maxValue ? newValue : m_maxValue);
}

void NumericalParameterWidget::decrement()
{
	double newValue = m_slider->value() - m_increment;
	m_doubleSpinBox->setValue(newValue > m_minValue ? newValue : m_minValue);
}
