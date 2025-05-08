#include "NavigationWidgetsCollectionPlugin.h"
#include "NavigationBranchWidgetPlugin.h"
#include "NavigationBreadcrumbWidgetPlugin.h"

NavigationWidgetsCollectionPlugin::NavigationWidgetsCollectionPlugin(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new NavigationBranchWidgetPlugin(this));
    m_widgets.append(new NavigationBreadcrumbWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface *> NavigationWidgetsCollectionPlugin::customWidgets() const
{
    return m_widgets;
}
