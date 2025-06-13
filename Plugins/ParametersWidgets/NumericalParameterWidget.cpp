#include "NumericalParameterWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QMargins>

NumericalParameterWidget::NumericalParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
    m_value(0),
	m_minValue(0),
	m_maxValue(100),
	m_increment(1.),
	m_isSliderUpdating(false),
	m_name("Numerical Parameter"),
	m_label(new QLabel("Numerical Parameter:", this)),
    m_slider(nullptr),
    m_doubleSpinBox(nullptr),
    m_lineEdit(nullptr),
    m_readOnly(readOnly)
{
    QHBoxLayout* layoutControls = new QHBoxLayout(this);
    layoutControls->addWidget(m_label);

    if (m_readOnly)
    {
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setPlaceholderText("Value");
        m_lineEdit->setEnabled(false);
        layoutControls->addWidget(m_lineEdit);
    }
    else
    {
        m_slider = new QSlider(Qt::Horizontal, this);
        m_doubleSpinBox = new QDoubleSpinBox(this);

        //layoutControls->addWidget(new QLabel(this)); // label vide pour faire un espace

        m_slider->setRange(m_minValue, m_maxValue);
        m_slider->setSingleStep(m_increment);
        m_doubleSpinBox->setRange(m_minValue, m_maxValue);
        m_doubleSpinBox->setSingleStep(m_increment);

        layoutControls->addWidget(m_slider,        /*stretch=*/1);
        layoutControls->addWidget(m_doubleSpinBox, /*stretch=*/1);

        connect(m_slider, &QSlider::valueChanged, this, &NumericalParameterWidget::onSliderValueChanged);
        connect(m_doubleSpinBox, &QDoubleSpinBox::valueChanged, this, &NumericalParameterWidget::onSpinBoxValueChanged);

        connect(m_doubleSpinBox, &QDoubleSpinBox::valueChanged, this, &NumericalParameterWidget::valueChanged);
    }
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
        if (m_slider)
        {
            m_slider->setMinimum(min);
            m_doubleSpinBox->setMinimum(min);
        }
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
        if (m_slider)
        {
            m_slider->setMaximum(max);
            m_doubleSpinBox->setMaximum(max);
        }
		emit maximumChanged(max);
		if (getValue() > m_maxValue)
		{
			setValue(m_maxValue);
		}
	}
}

double NumericalParameterWidget::getValue() const
{
    return m_value;
}

void NumericalParameterWidget::setValue(double val)
{
    double k = std::round((val - m_minValue) / m_increment);
    val = m_minValue + k * m_increment; // to be sure val is reachable

    if (!fuzzyCompare(m_value, val))
    {
        m_value = val;

        if (m_doubleSpinBox)
            m_doubleSpinBox->setValue(val);
        else if (m_lineEdit)
            m_lineEdit->setText(QString::number(m_value, 'f', 3));
    }
    else if (m_lineEdit && m_lineEdit->text().isEmpty())
    {
        m_lineEdit->setText(QString::number(m_value, 'f', 3));
    }
}

void NumericalParameterWidget::setIncrement(double increment)
{
	if (increment > 0. && m_increment != increment)
	{
		m_increment = increment;
        if (m_slider)
        {
            m_slider->setSingleStep(round(increment));
            m_doubleSpinBox->setSingleStep(increment);
        }
		emit incrementChanged(increment);
	}
}

double NumericalParameterWidget::getIncrement() const { return m_increment; }

int NumericalParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void NumericalParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

void NumericalParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly)
    {
        m_lineEdit->setEnabled(false);
    }
}

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
    double k = std::round((value - m_minValue) / m_increment);
    double val = m_minValue + k * m_increment; // to be sure val is reachable
    if (val != value)
    {
        m_doubleSpinBox->setValue(val);
    }
    else
    {
        m_isSliderUpdating = true;
        m_slider->setValue(static_cast<int>(value));
        m_isSliderUpdating = false;
    }
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
    setValue(newValue < m_maxValue ? newValue : m_maxValue);
}

void NumericalParameterWidget::decrement()
{
	double newValue = m_slider->value() - m_increment;
    setValue(newValue > m_minValue ? newValue : m_minValue);
}
