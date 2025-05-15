#include "NavigationLayoutWidgetPlugin.h"
#include "NavigationLayoutWidget.h"

#include <QtPlugin>

NavigationLayoutWidgetPlugin::NavigationLayoutWidgetPlugin(QObject *parent)
    : QObject(parent)
{}

void NavigationLayoutWidgetPlugin::initialize(QDesignerFormEditorInterface* core)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

bool NavigationLayoutWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavigationLayoutWidgetPlugin::createWidget(QWidget *parent)
{
    return new NavigationLayoutWidget(parent);
}

QString NavigationLayoutWidgetPlugin::name() const
{
    return QLatin1String("NavigationLayoutWidget");
}

QString NavigationLayoutWidgetPlugin::group() const
{
    return QLatin1String("Navigation Widgets");
}

QIcon NavigationLayoutWidgetPlugin::icon() const
{
    return QIcon();
}

QString NavigationLayoutWidgetPlugin::toolTip() const
{
    return QLatin1String("Navigation Layout Widget");
}

QString NavigationLayoutWidgetPlugin::whatsThis() const
{
    return QLatin1String("A Layout widget that includes a structure for building a multi-page "
                         "application. Depends on the NavigationWidgets and TogglePanel plugins.");
}

bool NavigationLayoutWidgetPlugin::isContainer() const
{
    return false;
}

QString NavigationLayoutWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<widget class="NavigationLayoutWidget" name="navigationLayoutWidget">
 <property name="treeDef">
  <string notr="true"><![CDATA[{
    "name": "root",
    "children": [
        { "name": "Item 1" },
        { "name": "Item 2", "enabled": false }
    ]
}]]></string>
 </property>
</widget>
)");
}

QString NavigationLayoutWidgetPlugin::includeFile() const
{
    return QLatin1String("NavigationLayoutWidget.h");
}
