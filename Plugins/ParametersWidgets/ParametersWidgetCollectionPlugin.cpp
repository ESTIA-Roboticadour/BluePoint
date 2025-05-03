#include "ParametersWidgetCollectionPlugin.h"
#include "BoolParameterWidgetPlugin.h"
#include "ListParameterWidgetPlugin.h"
#include "NumericalParameterWidgetPlugin.h"
#include "ParametersViewPlugin.h"
#include "StringParameterWidgetPlugin.h"

ParametersWidgetCollection::ParametersWidgetCollection(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new NumericalParameterWidgetPlugin(this));
    m_widgets.append(new BoolParameterWidgetPlugin(this));
    m_widgets.append(new StringParameterWidgetPlugin(this));
    m_widgets.append(new ListParameterWidgetPlugin(this));
    m_widgets.append(new ParametersViewPlugin(this));
}

QList<QDesignerCustomWidgetInterface *> ParametersWidgetCollection::customWidgets() const
{
    return m_widgets;
}
