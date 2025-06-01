#include "ListParameterWidget.h"
#include <QHBoxLayout>

ListParameterWidget::ListParameterWidget(QWidget* parent) :
	QWidget(parent),
	m_label(new QLabel("List Parameter:", this)),
	m_comboBox(new QComboBox(this))
{
    m_comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(m_label);
	mainLayout->addWidget(m_comboBox);

	connect(m_comboBox, &QComboBox::currentIndexChanged, this, &ListParameterWidget::selectedIndexChanged);
}

QString ListParameterWidget::getName() const
{
	return m_name;
}

QStringList ListParameterWidget::getOptions() const
{
	QStringList options;
	for (int i = 0; i < m_comboBox->count(); ++i)
	{
		options << m_comboBox->itemText(i);
	}
	return options;
}

int ListParameterWidget::getCurrentIndex() const
{
	return m_comboBox->currentIndex();
}

void ListParameterWidget::setFrom(const ListParameterBase* parameter)
{
	setName(parameter->getName());
	setOptions(parameter->getKeys());
	setCurrentIndex(parameter->getSelectedIndex());
	setEnabled(parameter->getIsEditable());
}

void ListParameterWidget::setName(const QString& name)
{
	if (m_name != name)
	{
		m_name = name;
		m_label->setText(name + ':');
		emit nameChanged(name);
	}
}

void ListParameterWidget::setOptions(const QStringList& keys)
{
	m_comboBox->clear();
	m_comboBox->addItems(keys);
    emit optionsChanged(keys);
}

void ListParameterWidget::setCurrentIndex(int index)
{
	if (index != m_comboBox->currentIndex())
	{
		m_comboBox->setCurrentIndex(index);
	}
}
