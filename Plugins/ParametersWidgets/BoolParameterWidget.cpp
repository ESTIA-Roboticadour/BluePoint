#include "BoolParameterWidget.h"
#include <QHBoxLayout>

BoolParameterWidget::BoolParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
    m_name("Bool Parameter"),
    m_label(new QLabel("Bool Parameter:")),
    m_checkBox(new QCheckBox(this)),
    m_readOnly(readOnly)
{
    m_checkBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QHBoxLayout* layoutControls = new QHBoxLayout(this);
    layoutControls->addWidget(m_label);
    layoutControls->addWidget(m_checkBox);
    layoutControls->addStretch();

    if (m_readOnly)
    {
        m_checkBox->setEnabled(false);
    }
    else
    {
        connect(m_checkBox, &QCheckBox::toggled, this, &BoolParameterWidget::valueChanged);
    }
}

QString BoolParameterWidget::getName() const
{
    return m_name;
}

void BoolParameterWidget::setName(const QString& newName)
{
    if (m_name != newName)
	{
        m_name = newName;
        m_label->setText(newName + ':');
		emit nameChanged(newName);
	}
}

void BoolParameterWidget::setValue(bool value)
{
	if (m_checkBox->isChecked() != value)
	{
		m_checkBox->setChecked(value);
	}
}

bool BoolParameterWidget::getValue() const
{
	return m_checkBox->isChecked();
}

int BoolParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void BoolParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

void BoolParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly)
    {
        m_checkBox->setEnabled(false);
    }
}

void BoolParameterWidget::setFrom(const BoolParameter* parameter)
{
	setName(parameter->getName());
	setValue(parameter->getValue());
	setEnabled(parameter->getIsEditable());
}
