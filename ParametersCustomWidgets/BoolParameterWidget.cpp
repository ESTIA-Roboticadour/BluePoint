#include "BoolParameterWidget.h"
#include <QVBoxLayout>

BoolParameterWidget::BoolParameterWidget(QWidget* parent) :
	QWidget(parent),
	m_checkBox(new QCheckBox("Bool Parameter", this))
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_checkBox);

	connect(m_checkBox, &QCheckBox::toggled, this, &BoolParameterWidget::valueChanged);
}

QString BoolParameterWidget::getName() const
{
	return m_checkBox->text();
}

void BoolParameterWidget::setName(const QString& newName)
{
	if (m_checkBox->text() != newName)
	{
		m_checkBox->setText(newName);
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

void BoolParameterWidget::setFrom(const BoolParameter* parameter)
{
	setName(parameter->getName());
	setValue(parameter->getValue());
	setEnabled(parameter->getIsEditable());
}
