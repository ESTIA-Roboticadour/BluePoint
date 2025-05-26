#include "AppLayoutWidgetPlugin.h"
#include "AppLayoutWidget.h"

#include <QtPlugin>

AppLayoutWidgetPlugin::AppLayoutWidgetPlugin(QObject *parent)
    : QObject(parent)
{}

void AppLayoutWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AppLayoutWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AppLayoutWidgetPlugin::createWidget(QWidget *parent)
{
    return new AppLayoutWidget(parent);
}

QString AppLayoutWidgetPlugin::name() const
{
    return QLatin1String("AppLayoutWidget");
}

QString AppLayoutWidgetPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon AppLayoutWidgetPlugin::icon() const
{
    return QIcon();
}

QString AppLayoutWidgetPlugin::toolTip() const
{
    return QLatin1String("Layout complet : navigation + background + logs");
}

QString AppLayoutWidgetPlugin::whatsThis() const
{
    return QLatin1String("Combinaison NavigationBranch / Breadcrumb, LayeredWidget, LogWidget");
}

bool AppLayoutWidgetPlugin::isContainer() const
{
    return false;
}

QString AppLayoutWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<widget class="AppLayoutWidget" name="appLayoutWidget">
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

QString AppLayoutWidgetPlugin::includeFile() const
{
    return QLatin1String("AppLayoutWidget.h");
}
