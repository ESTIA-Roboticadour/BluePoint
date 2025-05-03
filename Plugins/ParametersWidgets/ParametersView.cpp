#include "ParametersView.h"
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>

#include "BoolParameterWidget.h"
#include "NumericalParameterWidget.h"
#include "StringParameterWidget.h"
#include "ListParameterWidget.h"

ParametersView::ParametersView(QWidget* parent) :
	QWidget(parent),
	m_isReadOnly(false),
	m_layout(new QVBoxLayout(this)),
	m_parameters(nullptr)
{
	//setLayout(m_layout); fait automatiquement avec QVBoxLayout(this)
	setBoxLayoutSpacing(m_layout, 2, 2, 2, 2, 2);
}

ParametersView::~ParametersView()
{
	clear();
}

bool ParametersView::isReadOnly() const
{
	return m_isReadOnly;
}

void ParametersView::setReadOnly(bool readonly)
{
	if (m_isReadOnly != readonly)
	{
		m_isReadOnly = readonly;
		if (m_parameters)
			setParameters(*m_parameters, m_layout);
		emit readOnlyChanged(m_isReadOnly);
	}
}

void ParametersView::setBoxLayoutSpacing(QBoxLayout* layout, int spacing, int left, int top, int right, int bottom)
{
	layout->setSpacing(spacing);
	layout->setContentsMargins(left, top, right, bottom);
}

void ParametersView::clear()
{
	clearLayout(m_layout);
}

void ParametersView::clearLayout(QLayout* layout)
{
	if (!layout)
		return;

	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr)
	{
		// Si c'est un widget, on le supprime
		if (QWidget* widget = item->widget())
		{
			widget->disconnect();
			delete widget;
		}
		// Si c'est un layout enfant, on le nettoie récursivement
		else if (QLayout* childLayout = item->layout())
		{
			clearLayout(childLayout);  // récursivité ici
			delete childLayout;
		}
		// Supprimer le QLayoutItem lui-même
		delete item;
	}
}

void ParametersView::setParameters(const QList<const ParameterBase*>& parameters)
{
	clear();
	m_parameters = &parameters;
	setParameters(parameters, m_layout);
}

void ParametersView::setParameters(const QList<const ParameterBase*>& parameters, QLayout* layout)
{
	for (const ParameterBase* parameter : parameters)
	{
		QWidget* widget = createParameterWidget(parameter);
		if (widget)
		{
			if (auto boxLayout = qobject_cast<QBoxLayout*>(widget->layout()))
			{
				setBoxLayoutSpacing(boxLayout, 2, 6, 4, 6, 4);
			}
			layout->addWidget(widget);
		}
	}
}

QWidget* ParametersView::createParameterWidget(const ParameterBase* parameter)
{
	// Group
	if (auto groupParam = qobject_cast<const ParameterGroup*>(parameter))
	{
		return createParameterGroupWidget(groupParam);
	}
	// Boolean
	if (auto boolParam = qobject_cast<const BoolParameter*>(parameter))
	{
		return createBoolParameterWidget(boolParam);
	}
	// Numerical
	if (auto numericalParam = qobject_cast<const NumericalParameter*>(parameter))
	{
		return createNumericalParameterWidget(numericalParam);
	}
	// String
	if (auto stringParam = qobject_cast<const StringParameter*>(parameter))
	{
		return createStringParameterWidget(stringParam);
	}
	// List
	if (auto listParam = qobject_cast<const ListParameterBase*>(parameter))
	{
		return createListParameterWidget(listParam);
	}
	// Unknown
	return createUnknowParameterWidget(parameter);
}

QWidget* ParametersView::createParameterGroupWidget(const ParameterGroup* parameter)
{
	auto* box = new QGroupBox(parameter->getName());
	QVBoxLayout* layout = new QVBoxLayout();
	box->setLayout(layout);
	setParameters(parameter->getParameters(), layout);
	return box;
}

QWidget* ParametersView::createBoolParameterWidget(const BoolParameter* parameter) const
{
	QWidget* widget = nullptr;
	if (m_isReadOnly)
	{

		QCheckBox* checkBox = new QCheckBox(parameter->getName());
		checkBox->setChecked(parameter->getValue());
		checkBox->setEnabled(false);

		QWidget* container = new QWidget();
		QVBoxLayout* layout = new QVBoxLayout();
		layout->addWidget(checkBox);
		container->setLayout(layout);

		connect(parameter, &BoolParameter::valueChanged, checkBox, &QCheckBox::setChecked);

		widget = container;
	}
	else
	{
		auto* boolWidget = new BoolParameterWidget();
		boolWidget->setFrom(parameter);

		connect(boolWidget, &BoolParameterWidget::valueChanged, parameter, &BoolParameter::setValue);
		connect(parameter, &BoolParameter::valueChanged, boolWidget, &BoolParameterWidget::setValue);
		connect(parameter, &ParameterBase::isEditableChanged, boolWidget, &QWidget::setEnabled);

		widget = boolWidget;
	}
	return widget;
}

QWidget* ParametersView::createNumericalParameterWidget(const NumericalParameter* parameter) const
{
	QWidget* widget = nullptr;
	if (m_isReadOnly)
	{
		QWidget* container = new QWidget();
		QLabel* label = new QLabel(parameter->getName() + ": ");
		QLabel* valueLabel = new QLabel(QString::number(parameter->getValue()));

		QHBoxLayout* layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(valueLabel);
		container->setLayout(layout);

		connect(parameter, &NumericalParameter::valueChanged, [valueLabel](double value) {
			valueLabel->setText(QString::number(value));
			});

		widget = container;
	}
	else
	{
		auto* numericalWidget = new NumericalParameterWidget();
		numericalWidget->setFrom(parameter);

		connect(numericalWidget, &NumericalParameterWidget::valueChanged, parameter, &NumericalParameter::setValue);

		connect(parameter, &NumericalParameter::valueChanged, numericalWidget, &NumericalParameterWidget::setValue);
		connect(parameter, &NumericalParameter::minimumChanged, numericalWidget, &NumericalParameterWidget::setMinimum);
		connect(parameter, &NumericalParameter::maximumChanged, numericalWidget, &NumericalParameterWidget::setMaximum);
		connect(parameter, &NumericalParameter::incrementChanged, numericalWidget, &NumericalParameterWidget::setIncrement);
		connect(parameter, &ParameterBase::isEditableChanged, numericalWidget, &QWidget::setEnabled);

		widget = numericalWidget;
	}
	return widget;
}

QWidget* ParametersView::createStringParameterWidget(const StringParameter* parameter) const
{
	QWidget* widget = nullptr;
	if (m_isReadOnly)
	{
		QWidget* container = new QWidget();
		QLabel* label = new QLabel(parameter->getName() + ": ");
		QLabel* valueLabel = new QLabel(parameter->getValue());

		QHBoxLayout* layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(valueLabel);
		container->setLayout(layout);

		connect(parameter, &StringParameter::valueChanged, valueLabel, &QLabel::setText);

		widget = container;
	}
	else
	{
		auto* stringWidget = new StringParameterWidget();
		stringWidget->setFrom(parameter);

		connect(stringWidget, &StringParameterWidget::valueChanged, parameter, &StringParameter::setValue);

		connect(parameter, &StringParameter::valueChanged, stringWidget, &StringParameterWidget::setValue);
		connect(parameter, &ParameterBase::isEditableChanged, stringWidget, &QWidget::setEnabled);

		widget = stringWidget;
	}
	return widget;
}

QWidget* ParametersView::createListParameterWidget(const ListParameterBase* parameter) const
{
	QWidget* widget = nullptr;
	if (m_isReadOnly)
	{
		QWidget* container = new QWidget();
		QLabel* label = new QLabel(parameter->getName() + ": ");
		QLabel* valueLabel = new QLabel(parameter->getSelectedKey());

		QHBoxLayout* layout = new QHBoxLayout();
		layout->addWidget(label);
		layout->addWidget(valueLabel);
		container->setLayout(layout);

		connect(parameter, &ListParameterBase::selectedIndexChanged, [parameter, valueLabel](int index) {
			valueLabel->setText(parameter->getSelectedKey());
			});

		widget = container;
	}
	else
	{
		auto listWidget = new ListParameterWidget();
		listWidget->setFrom(parameter);

		connect(listWidget, &ListParameterWidget::selectedIndexChanged, parameter, &ListParameterBase::selectValueByIndex);
		connect(parameter, &ParameterBase::isEditableChanged, listWidget, &QWidget::setEnabled);
		connect(parameter, &ListParameterBase::selectedIndexChanged, listWidget, &ListParameterWidget::setCurrentIndex);

		widget = listWidget;
	}
	return widget;
}

QWidget* ParametersView::createUnknowParameterWidget(const ParameterBase* parameter) const
{
	QWidget* container = new QWidget();
	QLabel* label = new QLabel(parameter->getName());

	QHBoxLayout* layout = new QHBoxLayout();
	layout->addWidget(label);
	container->setLayout(layout);

	return container;
}
