#include "ParametersView.h"
#include "ParameterWidget.h"
#include "BoolParameterWidget.h"
#include "NumericalParameterWidget.h"
#include "StringParameterWidget.h"
#include "ListParameterWidget.h"

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
    m_parameters(nullptr),
    m_alignment(ParametersView::Alignment::NoAlignment),
    m_maxWidthPerLevel()
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
		if (m_parameters)
			setParameters(*m_parameters, m_layout);
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
    m_maxWidthPerLevel.clear();
}

void ParametersView::setParameters(const QList<const ParameterBase*>& parameters)
{
	clear();
    m_parameters = &parameters;
    //qDebug() << "--";
    //qDebug() << findMaxDepth(parameters);
    //qDebug() << "--";
    m_maxWidthPerLevel.fill(0, findMaxDepth(parameters));
	setParameters(parameters, m_layout);
}

void ParametersView::setParameters(const QList<const ParameterBase*>& parameters, QLayout* layout)
{
    //qDebug() << "--------------";
    setParametersAndSetMaxWidth(parameters, layout, 0);
    //qDebug() << "--------------";
    //for (auto w : m_maxWidthPerLevel)
    //    qDebug() << w;

    if (m_alignment != ParametersView::Alignment::NoAlignment)
        updateWidgetsAlignment();
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

void ParametersView::setParametersAndSetMaxWidth(const QList<const ParameterBase*>& parameters, QLayout* layout, int depth)
{
    for (const ParameterBase* parameter : parameters)
    {
        int width;
        QWidget* widget = createParameterWidget(parameter, depth, &width);
        if (widget)
        {
            //qDebug() << parameter->getName() << ':' << width;
            if (width > m_maxWidthPerLevel[depth])
            {
                m_maxWidthPerLevel[depth] = width;
            }

            if (auto boxLayout = qobject_cast<QBoxLayout*>(widget->layout()))
            {
                setBoxLayoutSpacing(boxLayout, 2, 6, 4, 6, 4);
            }
            layout->addWidget(widget);
        }
    }
}

QWidget* ParametersView::createParameterWidget(const ParameterBase* parameter, int depth, int* width)
{
	// Group
	if (auto groupParam = qobject_cast<const GroupParameter*>(parameter))
	{
        return createParameterGroupWidget(groupParam, depth, width);
	}
	// Boolean
	if (auto boolParam = qobject_cast<const BoolParameter*>(parameter))
	{
        return createBoolParameterWidget(boolParam, width);
	}
	// Numerical
	if (auto numericalParam = qobject_cast<const NumericalParameter*>(parameter))
	{
        return createNumericalParameterWidget(numericalParam, width);
	}
	// String
	if (auto stringParam = qobject_cast<const StringParameter*>(parameter))
	{
        return createStringParameterWidget(stringParam, width);
	}
	// List
	if (auto listParam = qobject_cast<const ListParameterBase*>(parameter))
	{
        return createListParameterWidget(listParam, width);
	}
	// Unknown
    return createUnknowParameterWidget(parameter, width);
}

QWidget* ParametersView::createParameterGroupWidget(const GroupParameter* parameter, int depth, int* width)
{
    *width = -1;
    QGroupBox* box = new QGroupBox(parameter->getName());
	QVBoxLayout* layout = new QVBoxLayout();
	box->setLayout(layout);
    setParametersAndSetMaxWidth(parameter->getParameters(), layout, depth + 1);
	return box;
}

QWidget* ParametersView::createBoolParameterWidget(const BoolParameter* parameter, int* width) const
{
    BoolParameterWidget* boolWidget = new BoolParameterWidget(m_isReadOnly);
    boolWidget->setFrom(parameter);
    *width = boolWidget->getLabelWidth();

    connect(parameter, &BoolParameter::valueChanged, boolWidget, &BoolParameterWidget::setValue);

    if (!m_isReadOnly)
	{
		connect(boolWidget, &BoolParameterWidget::valueChanged, parameter, &BoolParameter::setValue);
        connect(parameter, &ParameterBase::isEditableChanged, boolWidget, &BoolParameterWidget::setEnabled);
	}
    return boolWidget;
}

QWidget* ParametersView::createNumericalParameterWidget(const NumericalParameter* parameter, int* width) const
{
    NumericalParameterWidget* numericalWidget = new NumericalParameterWidget(m_isReadOnly);
    numericalWidget->setFrom(parameter);
    *width = numericalWidget->getLabelWidth();

    connect(parameter, &NumericalParameter::valueChanged, numericalWidget, &NumericalParameterWidget::setValue);

    if (!m_isReadOnly)
	{
		connect(numericalWidget, &NumericalParameterWidget::valueChanged, parameter, &NumericalParameter::setValue);
        connect(parameter, &NumericalParameter::minimumChanged, numericalWidget, &NumericalParameterWidget::setMinimum);
        connect(parameter, &NumericalParameter::maximumChanged, numericalWidget, &NumericalParameterWidget::setMaximum);
        connect(parameter, &NumericalParameter::incrementChanged, numericalWidget, &NumericalParameterWidget::setIncrement);
        connect(parameter, &ParameterBase::isEditableChanged, numericalWidget, &NumericalParameterWidget::setEnabled);
	}
    return numericalWidget;
}

QWidget* ParametersView::createStringParameterWidget(const StringParameter* parameter, int* width) const
{
    StringParameterWidget* stringWidget = new StringParameterWidget(m_isReadOnly);
    stringWidget->setFrom(parameter);
    *width = stringWidget->getLabelWidth();

    connect(parameter, &StringParameter::valueChanged, stringWidget, &StringParameterWidget::setValue);

    if (!m_isReadOnly)
	{
        connect(stringWidget, &StringParameterWidget::valueChanged, parameter, &StringParameter::setValue);
        connect(stringWidget, &StringParameterWidget::kindChanged, parameter, &StringParameter::setKind);
        connect(stringWidget, &StringParameterWidget::canEditPathChanged, parameter, &StringParameter::setCanEditPath);


        connect(parameter, &StringParameter::kindChanged, stringWidget, &StringParameterWidget::setKind);
        connect(parameter, &StringParameter::canEditPathChanged, stringWidget, &StringParameterWidget::setCanEditPath);
        connect(parameter, &ParameterBase::isEditableChanged, stringWidget, &QWidget::setEnabled);
	}
    return stringWidget;
}

QWidget* ParametersView::createListParameterWidget(const ListParameterBase* parameter, int* width) const
{
    ListParameterWidget* listWidget = new ListParameterWidget();
    listWidget->setFrom(parameter);
    *width = listWidget->getLabelWidth();

    connect(parameter, &ListParameterBase::selectedIndexChanged, listWidget, &ListParameterWidget::setCurrentIndex);

    if (!m_isReadOnly)
	{
		connect(listWidget, &ListParameterWidget::selectedIndexChanged, parameter, &ListParameterBase::selectValueByIndex);
		connect(parameter, &ParameterBase::isEditableChanged, listWidget, &QWidget::setEnabled);
	}
    return listWidget;
}

QWidget* ParametersView::createUnknowParameterWidget(const ParameterBase* parameter, int* width) const
{
	QWidget* container = new QWidget();
	QLabel* label = new QLabel(parameter->getName());
    *width = label->sizeHint().width();

    QHBoxLayout* layout = new QHBoxLayout(container);
	layout->addWidget(label);
	return container;
}

void ParametersView::updateWidgetsAlignment()
{
    if (m_alignment == Alignment::NoAlignment || m_maxWidthPerLevel.isEmpty())
        return;

    // Décalage visuel pour l’alignement global "All" :
    int INDENT_PER_DEPTH =
        QApplication::style()->pixelMetric(QStyle::PM_DefaultFrameWidth)  // bordure du QGroupBox
        + 6  // left-margin du layout de groupe (setContentsMargins)
        + 6; // left-margin du layout interne de chaque ParameterWidget

    // ---------------------------------------------------------------------
    // Récursion : parcourt tous les widgets contenus dans 'layout'.
    // ---------------------------------------------------------------------
    std::function<void(QLayout*, int)> applyWidths =
        [this, &applyWidths, INDENT_PER_DEPTH](QLayout* layout, int depth)
    {
        if (!layout) return;

        const int itemCount = layout->count();
        for (int i = 0; i < itemCount; ++i)
        {
            QLayoutItem* item = layout->itemAt(i);
            if (!item)
                continue;

            QWidget* currentWidget = item->widget();

            //-----------------------------------------------------------------
            // 1) Sous-groupe : on descend d’un niveau
            //-----------------------------------------------------------------
            if (auto* box = qobject_cast<QGroupBox*>(currentWidget))
            {
                applyWidths(box->layout(), depth + 1);
                continue;
            }

            //-----------------------------------------------------------------
            // 2) Paramètre 'classique' (hérite de ParameterWidget)
            //-----------------------------------------------------------------
            if (auto* pWidget = qobject_cast<ParameterWidget*>(currentWidget))
            {
                int targetWidth =
                    (m_alignment == Alignment::ByGroup)
                        ? m_maxWidthPerLevel[depth]                                   // largeur locale au niveau
                        : m_maxWidthPerLevel[depth] + (m_maxWidthPerLevel.size() - depth - 1) * INDENT_PER_DEPTH;       // alignement global

                pWidget->setLabelWidth(targetWidth);
                continue;
            }

            //-----------------------------------------------------------------
            // 3) Widget 'inconnu' : on cherche un QLabel en 1re position
            //-----------------------------------------------------------------
            if (currentWidget && currentWidget->layout())
            {
                QLayout* innerLayout = currentWidget->layout();
                if (innerLayout->count() > 0)
                {
                    QWidget* maybeLabelW = innerLayout->itemAt(0)->widget();
                    if (auto* lbl = qobject_cast<QLabel*>(maybeLabelW))
                    {
                        int targetWidth = (m_alignment == Alignment::ByGroup) ?
                                              m_maxWidthPerLevel[depth] :
                                              m_maxWidthPerLevel[depth] + (m_maxWidthPerLevel.size() - depth - 1) * INDENT_PER_DEPTH;

                        lbl->setFixedWidth(targetWidth);
                    }
                }
            }
        }
    };

    // Lancement à partir du layout racine
    applyWidths(m_layout, 0);
}

