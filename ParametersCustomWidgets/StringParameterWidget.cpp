#include "StringParameterWidget.h"

#include <QHBoxLayout>

StringParameterWidget::StringParameterWidget(QWidget* parent) :
	QWidget(parent),
	m_name("String Parameter"),
	m_label(new QLabel("String Parameter:", this)),
	m_lineEdit(new QLineEdit(this))
{
	m_lineEdit->setPlaceholderText("Value");
	QHBoxLayout* layoutControls = new QHBoxLayout;
	layoutControls->addWidget(m_label);
	layoutControls->addWidget(m_lineEdit);

	setLayout(layoutControls);

	connect(m_lineEdit, &QLineEdit::editingFinished, this, &StringParameterWidget::onEditingFinished);
}

QString StringParameterWidget::getName() const { return m_name; }

void StringParameterWidget::setName(const QString& newName)
{
	if (m_name != newName)
	{
		m_name = newName;
		m_label->setText(m_name + ':');
		emit nameChanged(newName);
	}
}

QString StringParameterWidget::getValue() const { return m_lineEdit->text(); }

void StringParameterWidget::setFrom(const StringParameter* parameter)
{
	setName(parameter->getName());
	setValue(parameter->getValue());
	setEnabled(parameter->getIsEditable());
}

void StringParameterWidget::setValue(const QString& val) { m_lineEdit->setText(val); }

void StringParameterWidget::onEditingFinished()
{
	emit valueChanged(m_lineEdit->text());
}
