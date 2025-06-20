#include "NumericalParameterWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QMargins>
#include <QSignalBlocker>

NumericalParameterWidget::NumericalParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
    m_value(0),
	m_minValue(0),
	m_maxValue(100),
	m_increment(1.),
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
        m_lineEdit->setText(QString::number(m_value, 'f', 3));
        m_lineEdit->setEnabled(false);
        layoutControls->addWidget(m_lineEdit);
    }
    else
    {
        m_slider = new QSlider(Qt::Horizontal, this);
        m_doubleSpinBox = new QDoubleSpinBox(this);
        m_slider->setRange(0, 100);
        m_slider->setSingleStep(1);
        m_doubleSpinBox->setDecimals(0); // default value : 0 -> 100, step : 1 -> no decimal needed
        m_doubleSpinBox->setRange(m_minValue, m_maxValue);
        m_doubleSpinBox->setSingleStep(m_increment);

        layoutControls->addWidget(m_slider,        /*stretch=*/1);
        layoutControls->addWidget(m_doubleSpinBox, /*stretch=*/1);

        connect(m_slider, &QSlider::valueChanged, this, &NumericalParameterWidget::onSliderValueChanged);
        connect(m_doubleSpinBox, &QDoubleSpinBox::editingFinished, this, &NumericalParameterWidget::onSpinBoxEditFinished);


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
    if (m_minValue != min && min < m_maxValue)
	{
		m_minValue = min;
        if (m_doubleSpinBox)
            m_doubleSpinBox->setMinimum(min);

		emit minimumChanged(min);

		if (getValue() < m_minValue)
			setValue(m_minValue);
	}
}

double NumericalParameterWidget::getMaximum() const { return m_maxValue; }

void NumericalParameterWidget::setMaximum(double max)
{
	if (m_maxValue != max && max > m_minValue)
	{
		m_maxValue = max;
        if (m_doubleSpinBox)
            m_doubleSpinBox->setMaximum(max);

		emit maximumChanged(max);
		if (getValue() > m_maxValue)
			setValue(m_maxValue);
	}
}

double NumericalParameterWidget::getValue() const
{
    return m_value;
}

void NumericalParameterWidget::setValue(double val)
{
    if (val < m_minValue)
        val = m_minValue;
    else if (val > m_maxValue)
        val = m_maxValue;

    double k = std::round((val - m_minValue) / m_increment);
    val = m_minValue + k * m_increment; // to be sure val is reachable

    if (!fuzzyCompare(m_value, val))
        m_value = val;

    if (m_doubleSpinBox)
        m_doubleSpinBox->setValue(m_value);

    if (m_slider)
    {
        QSignalBlocker blocker(m_slider);
        m_slider->setValue(static_cast<int>(100. * (m_value - m_minValue) / (m_maxValue - m_minValue)));
    }

    if (m_lineEdit)
        m_lineEdit->setText(QString::number(m_value, 'f', 3));
}

void NumericalParameterWidget::setIncrement(double increment)
{
    if (increment <= 0.)
        increment = 0.001;
    else if (increment >= (m_maxValue - m_minValue))
        increment = m_maxValue - m_minValue;

    if (m_increment != increment)
	{
		m_increment = increment;
        if (m_doubleSpinBox)
            m_doubleSpinBox->setSingleStep(increment);

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
    setIncrement(parameter->getIncrement());
	setMinimum(parameter->getMinimum());
	setMaximum(parameter->getMaximum());

    // set precision before setValue
    if (m_doubleSpinBox)
    {
        double tmp = m_value;
        m_value = parameter->getValue();
        m_doubleSpinBox->setDecimals(findBestPrecision());
        m_value = tmp;
    }

	setValue(parameter->getValue());
    setEnabled(parameter->getIsEditable());
}

void NumericalParameterWidget::onSpinBoxEditFinished()
{
    setValue(m_doubleSpinBox->value());
}

void NumericalParameterWidget::onSliderValueChanged(int value)
{
    m_doubleSpinBox->setValue(((static_cast<double>(value) / 100.) * (m_maxValue - m_minValue)) + m_minValue);
}

void NumericalParameterWidget::increment()
{
    double newValue = m_value + m_increment;
    setValue(newValue < m_maxValue ? newValue : m_maxValue);
}

void NumericalParameterWidget::decrement()
{
    double newValue = m_value - m_increment;
    setValue(newValue > m_minValue ? newValue : m_minValue);
}

int NumericalParameterWidget::countDecimals(double value, const int maxDecimals)
{
    // Ignore les entiers
    if (value == std::floor(value))
        return 0;

    double intPart;
    double fracPart = std::modf(value, &intPart);

    int decimals = 0;
    while (decimals < maxDecimals) {
        fracPart *= 10;
        double digit;
        fracPart = std::modf(fracPart, &digit);
        decimals++;

        if (fracPart == 0.0)
            break;
    }
    return decimals;
}

int NumericalParameterWidget::findBestPrecision() const
{
    return std::max({
        countDecimals(m_minValue, 6),
        countDecimals(m_maxValue, 6),
        countDecimals(m_value, 6),
        countDecimals(m_increment, 6)
    });
}
