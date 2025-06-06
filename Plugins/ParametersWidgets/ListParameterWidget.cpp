#include "ListParameterWidget.h"
#include <QHBoxLayout>

ListParameterWidget::ListParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
	m_label(new QLabel("List Parameter:", this)),
    m_comboBox(nullptr),
    m_lineEdit(nullptr),
    m_selectedIndex(-1),
    m_options(),
    m_readOnly(readOnly)
{
    QHBoxLayout* layoutControls = new QHBoxLayout(this);
    layoutControls->addWidget(m_label);

    if (m_readOnly)
    {
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setEnabled(false);
        layoutControls->addWidget(m_lineEdit);
    }
    else
    {
        m_comboBox = new QComboBox(this);
        m_comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        layoutControls->addWidget(m_comboBox);

        connect(m_comboBox, &QComboBox::currentIndexChanged, this, &ListParameterWidget::selectedIndexChanged);
    }
}

QString ListParameterWidget::getName() const
{
	return m_name;
}

QStringList ListParameterWidget::getOptions() const
{
	QStringList options;
    for (auto item : m_options)
        options.append(item);
	return options;
}

int ListParameterWidget::getCurrentIndex() const
{
    return m_selectedIndex;
}

int ListParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void ListParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

void ListParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly)
    {
        m_lineEdit->setEnabled(false);
    }
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
    m_selectedIndex = -1;
    m_options.clear();
    m_options.append(keys);

    if (m_comboBox)
    {
        m_comboBox->clear();
        m_comboBox->addItems(m_options);
    }
    emit optionsChanged(keys);
}

void ListParameterWidget::setCurrentIndex(int index)
{
    if (index != m_selectedIndex && index > 0 && index < m_options.size())
	{
        m_selectedIndex = index;
        if (m_comboBox)
            m_comboBox->setCurrentIndex(index);
        else
            m_lineEdit->setText(m_options[index]);
	}
}
