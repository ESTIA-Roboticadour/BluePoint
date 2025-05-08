#include "NavigationBreadcrumbWidget.h"
#include "NavigationBreadcrumbWidgetPlugin.h"

#include <QtPlugin>

NavigationBreadcrumbWidgetPlugin::NavigationBreadcrumbWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

void NavigationBreadcrumbWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavigationBreadcrumbWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavigationBreadcrumbWidgetPlugin::createWidget(QWidget *parent)
{
    return new NavigationBreadcrumbWidget(parent);
}

QString NavigationBreadcrumbWidgetPlugin::name() const
{
    return QLatin1String("NavigationBreadcrumbWidget");
}

QString NavigationBreadcrumbWidgetPlugin::group() const
{
    return QLatin1String("Navigation Widgets");
}

QIcon NavigationBreadcrumbWidgetPlugin::icon() const
{
    return QIcon();
}

QString NavigationBreadcrumbWidgetPlugin::toolTip() const
{
    return QLatin1String("Navigation Breadcrumb Widget");
}

QString NavigationBreadcrumbWidgetPlugin::whatsThis() const
{
    return QLatin1String("A horizontal breadcrumb bar that displays the full path from the root node to the current node. Every ancestor segment is a flat‑style button, letting users jump back up the hierarchy, while the last segment is a non‑clickable label.");
}

bool NavigationBreadcrumbWidgetPlugin::isContainer() const
{
    return false;
}

QString NavigationBreadcrumbWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="NavigationBreadcrumbWidget" name="navigationBreadcrumbWidget">
    <property name="minimumSize">
        <size>
            <width>60</width>
            <height>40</height>
        </size>
    </property>
</widget>)");
}

QString NavigationBreadcrumbWidgetPlugin::includeFile() const
{
    return QLatin1String("NavigationBreadcrumbWidget.h");
}
