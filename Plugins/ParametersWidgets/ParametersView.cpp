#include "ParametersView.h"
#include "BoolParameterWidget.h"
#include "NumericalParameterWidget.h"
#include "StringParameterWidget.h"
#include "ListParameterWidget.h"
#include "Matrix4x4ParameterWidget.h"
#include "EulerFrameParameterWidget.h"
#include "UnknownParameterWidget.h"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QApplication>
#include <algorithm>   // std::max

ParametersView::ParametersView(QWidget* parent) :
	QWidget(parent),
	m_isReadOnly(false),
	m_layout(new QVBoxLayout(this)),
    m_parameters(),
    m_alignment(ParametersView::Alignment::NoAlignment),
    m_stackedGroupBoxes(),
    m_groupsInfo()
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

ParametersView::Alignment ParametersView::alignment() const
{
    return m_alignment;
}

void ParametersView::setReadOnly(bool readonly)
{
	if (m_isReadOnly != readonly)
	{
		m_isReadOnly = readonly;
        buildUI(m_parameters);
		emit readOnlyChanged(m_isReadOnly);
	}
}

void ParametersView::setAlignment(ParametersView::Alignment alignment)
{
    if (m_alignment != alignment)
    {
        m_alignment = alignment;
        updateWidgetsAlignment();
        emit alignmentChanged(m_alignment);
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

int ParametersView::findMaxDepth(const QList<const ParameterBase*>& params) const
{
    int maxDepth = 1;                       // profondeur du niveau courant

    for (const ParameterBase* param : params)
    {
        if (const auto* group = qobject_cast<const GroupParameter*>(param))
        {
            // profondeur dans la branche du sous-groupe + 1 (le groupe courant)
            int childDepth = 1 + findMaxDepth(group->getParameters());
            maxDepth = std::max(maxDepth, childDepth);
        }
    }
    return maxDepth;
}

void ParametersView::setParameters(const QList<ParameterBase*>& parameters)
{
    QList<const ParameterBase*> constParams;
    for (auto* param : parameters)
    {
        constParams.append(param);
    }
    setParameters(constParams);
}

void ParametersView::setParameters(const QList<const ParameterBase*>& parameters)
{
    m_parameters = parameters;
    buildUI(parameters);
}

void ParametersView::buildUI(const QList<const ParameterBase*>& parameters)
{
    clear();
    m_stackedGroupBoxes.clear();
    m_groupsInfo.clear();
    m_groupsInfo.insert(nullptr, GroupInfo());
    buildUI(parameters, m_layout);

    if (m_alignment != ParametersView::Alignment::NoAlignment)
        updateWidgetsAlignment();
}

void ParametersView::buildUI(const QList<const ParameterBase*>& parameters, QLayout* layout)
{
    for (const ParameterBase* parameter : parameters)
    {
        QWidget* widget = createParameterWidget(parameter);
        if (widget)
        {
            if (auto paramWidget = qobject_cast<ParameterWidget*>(widget))
            {
                feedGroupInfo(paramWidget);
            }

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
	if (auto groupParam = qobject_cast<const GroupParameter*>(parameter))
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
    // Matrix4X4
    if (auto matrixParam = qobject_cast<const Matrix4x4Parameter*>(parameter))
    {
        return createMatrix4x4ParameterWidget(matrixParam);
    }
    // EulerFrameParameter
    if (auto eulerFrameParam = qobject_cast<const EulerFrameParameter*>(parameter))
    {
        return createEulerFrameParameter(eulerFrameParam);
    }
	// Unknown
    return createUnknownParameterWidget(parameter);
}

QWidget* ParametersView::createParameterGroupWidget(const GroupParameter* parameter)
{
    QGroupBox* box = new QGroupBox(parameter->getName());
    createGroupInfo(box);
	QVBoxLayout* layout = new QVBoxLayout();
	box->setLayout(layout);
    buildUI(parameter->getParameters(), layout);
    m_stackedGroupBoxes.pop();
	return box;
}

ParameterWidget* ParametersView::createBoolParameterWidget(const BoolParameter* parameter)
{
    BoolParameterWidget* boolWidget = new BoolParameterWidget(m_isReadOnly);
    boolWidget->setFrom(parameter);

    connect(parameter, &BoolParameter::valueChanged, boolWidget, &BoolParameterWidget::setValue);

    if (!m_isReadOnly)
	{
		connect(boolWidget, &BoolParameterWidget::valueChanged, parameter, &BoolParameter::setValue);
        connect(parameter, &ParameterBase::isEditableChanged, boolWidget, &BoolParameterWidget::setEnabled);
	}
    return boolWidget;
}

ParameterWidget* ParametersView::createNumericalParameterWidget(const NumericalParameter* parameter)
{
    NumericalParameterWidget* numericalWidget = new NumericalParameterWidget(m_isReadOnly);
    numericalWidget->setFrom(parameter);

    connect(parameter, &NumericalParameter::valueChanged, numericalWidget, &NumericalParameterWidget::setValue);
    connect(parameter, &NumericalParameter::minimumChanged, numericalWidget, &NumericalParameterWidget::setMinimum);
    connect(parameter, &NumericalParameter::maximumChanged, numericalWidget, &NumericalParameterWidget::setMaximum);
    connect(parameter, &NumericalParameter::incrementChanged, numericalWidget, &NumericalParameterWidget::setIncrement);

    if (!m_isReadOnly)
	{
		connect(numericalWidget, &NumericalParameterWidget::valueChanged, parameter, &NumericalParameter::setValue);
        connect(parameter, &ParameterBase::isEditableChanged, numericalWidget, &NumericalParameterWidget::setEnabled);
	}
    return numericalWidget;
}

ParameterWidget* ParametersView::createStringParameterWidget(const StringParameter* parameter)
{
    StringParameterWidget* stringWidget = new StringParameterWidget(m_isReadOnly);
    stringWidget->setFrom(parameter);

    connect(parameter, &StringParameter::valueChanged, stringWidget, &StringParameterWidget::setValue);
    connect(parameter, &StringParameter::kindChanged, stringWidget, &StringParameterWidget::setKind);
    connect(parameter, &StringParameter::canEditPathChanged, stringWidget, &StringParameterWidget::setCanEditPath);

    if (!m_isReadOnly)
	{
        connect(stringWidget, &StringParameterWidget::valueChanged, parameter, &StringParameter::setValue);
        connect(stringWidget, &StringParameterWidget::kindChanged, parameter, &StringParameter::setKind);
        connect(stringWidget, &StringParameterWidget::canEditPathChanged, parameter, &StringParameter::setCanEditPath);
        connect(parameter, &ParameterBase::isEditableChanged, stringWidget, &StringParameterWidget::setEnabled);
	}
    return stringWidget;
}

ParameterWidget* ParametersView::createListParameterWidget(const ListParameterBase* parameter)
{
    ListParameterWidget* listWidget = new ListParameterWidget(m_isReadOnly);
    listWidget->setFrom(parameter);

    connect(parameter, &ListParameterBase::selectedIndexChanged, listWidget, &ListParameterWidget::setCurrentIndex);

    if (!m_isReadOnly)
	{
		connect(listWidget, &ListParameterWidget::selectedIndexChanged, parameter, &ListParameterBase::selectValueByIndex);
        connect(parameter, &ParameterBase::isEditableChanged, listWidget, &ListParameterWidget::setEnabled);
	}
    return listWidget;
}

ParameterWidget* ParametersView::createMatrix4x4ParameterWidget(const Matrix4x4Parameter* parameter)
{
    Matrix4x4ParameterWidget* matrixWidget = new Matrix4x4ParameterWidget(m_isReadOnly);
    matrixWidget->setFrom(parameter);

    connect(parameter, &Matrix4x4Parameter::matrixChanged, matrixWidget, &Matrix4x4ParameterWidget::setValue);

    if (!m_isReadOnly)
    {
        connect(matrixWidget, &Matrix4x4ParameterWidget::matrixChanged, parameter, static_cast<void (Matrix4x4Parameter::*)(const QMatrix4x4&)>(&Matrix4x4Parameter::setValue));
        connect(parameter, &ParameterBase::isEditableChanged, matrixWidget, &Matrix4x4ParameterWidget::setEnabled);
    }
    return matrixWidget;
}

ParameterWidget* ParametersView::createEulerFrameParameter(const EulerFrameParameter* parameter)
{
    EulerFrameParameterWidget* eulerWidget = new EulerFrameParameterWidget(m_isReadOnly);
    eulerWidget->setFrom(parameter);

    connect(parameter, &EulerFrameParameter::conventionChanged, eulerWidget, &EulerFrameParameterWidget::setConvention);
    connect(parameter, &EulerFrameParameter::xChanged, eulerWidget, &EulerFrameParameterWidget::setX);
    connect(parameter, &EulerFrameParameter::yChanged, eulerWidget, &EulerFrameParameterWidget::setY);
    connect(parameter, &EulerFrameParameter::zChanged, eulerWidget, &EulerFrameParameterWidget::setZ);
    connect(parameter, &EulerFrameParameter::aChanged, eulerWidget, &EulerFrameParameterWidget::setA);
    connect(parameter, &EulerFrameParameter::bChanged, eulerWidget, &EulerFrameParameterWidget::setB);
    connect(parameter, &EulerFrameParameter::cChanged, eulerWidget, &EulerFrameParameterWidget::setC);

    if (!m_isReadOnly)
    {
        connect(eulerWidget, &EulerFrameParameterWidget::xChanged, parameter, &EulerFrameParameter::setX);
        connect(eulerWidget, &EulerFrameParameterWidget::yChanged, parameter, &EulerFrameParameter::setY);
        connect(eulerWidget, &EulerFrameParameterWidget::zChanged, parameter, &EulerFrameParameter::setZ);
        connect(eulerWidget, &EulerFrameParameterWidget::aChanged, parameter, &EulerFrameParameter::setA);
        connect(eulerWidget, &EulerFrameParameterWidget::bChanged, parameter, &EulerFrameParameter::setB);
        connect(eulerWidget, &EulerFrameParameterWidget::cChanged, parameter, &EulerFrameParameter::setC);
        connect(eulerWidget, &EulerFrameParameterWidget::conventionChanged, parameter, &EulerFrameParameter::setConvention);

        connect(parameter, &ParameterBase::isEditableChanged, eulerWidget, &EulerFrameParameterWidget::setEnabled);
    }

    return eulerWidget;
}

ParameterWidget* ParametersView::createUnknownParameterWidget(const ParameterBase* parameter)
{
    UnknownParameterWidget* widget = new UnknownParameterWidget();
    widget->setFrom(parameter);
	return widget;
}

void ParametersView::createGroupInfo(const QGroupBox* groupBox)
{
    GroupInfo groupInfo;
    m_stackedGroupBoxes.push(groupBox);
    int stackSize = m_stackedGroupBoxes.size();
    groupInfo.level = stackSize;
    int groupBoxThickness = QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    int leftMarginPerLevel = 8; // 2 (spacing) + 6 (margin left)
    groupInfo.leftMargin = stackSize * leftMarginPerLevel + (stackSize - 1) * groupBoxThickness;

    m_groupsInfo.insert(groupBox, groupInfo);
}

void ParametersView::feedGroupInfo(ParameterWidget* widget)
{
    const QGroupBox* groupBox = m_stackedGroupBoxes.isEmpty() ? nullptr : m_stackedGroupBoxes.top();
    auto groupInfoIt = m_groupsInfo.find(groupBox);
    GroupInfo& info = groupInfoIt.value();
    int width = widget->getLabelWidth();
    if (width > info.maxWidth)
    {
        info.maxWidth = width;
    }
    info.children.append(widget);
}

void ParametersView::updateWidgetsAlignment()
{
    if (m_alignment == Alignment::NoAlignment)
        return;

    int longestWidth = 0;
    if (m_alignment == Alignment::All)
    {
        for (auto& group : m_groupsInfo)
        {
            int width = group.leftMargin + group.maxWidth;
            if (width > longestWidth)
                longestWidth = width;
        }
    }
    int groupBoxThickness = QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    int leftMarginPerLevel = 8; // 2 (spacing) + 6 (margin left)

    for (auto& group : m_groupsInfo)
    {
        for (auto& child : group.children)
        {
            if (m_alignment == Alignment::All)
            {
                int margin = group.level * leftMarginPerLevel + std::max(0, group.level - 1) * groupBoxThickness;
                child->setLabelWidth(longestWidth - margin);
            }
            else
            {
                child->setLabelWidth(group.maxWidth);
            }
        }
    }
}
