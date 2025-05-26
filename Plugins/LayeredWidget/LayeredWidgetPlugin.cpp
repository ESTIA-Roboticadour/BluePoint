#include "LayeredWidgetPlugin.h"
#include "LayeredWidget.h"

#include <QtPlugin>

LayeredWidgetPlugin::LayeredWidgetPlugin(QObject *parent)
    : QObject(parent)
{}

void LayeredWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LayeredWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LayeredWidgetPlugin::createWidget(QWidget *parent)
{
    return new LayeredWidget(parent);
}

QString LayeredWidgetPlugin::name() const
{
    return QLatin1String("LayeredWidget");
}

QString LayeredWidgetPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon LayeredWidgetPlugin::icon() const
{
    return QIcon();
}

QString LayeredWidgetPlugin::toolTip() const
{
    return QLatin1String("Overlay two widgets with opacity + filter");
}

QString LayeredWidgetPlugin::whatsThis() const
{
    return QLatin1String("Composite widget: background + foreground + colour/alpha filter");
}

bool LayeredWidgetPlugin::isContainer() const
{
    return false;
}

QString LayeredWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="LayeredWidget" name="layeredWidget">
</widget>)");
}

QString LayeredWidgetPlugin::includeFile() const
{
    return QLatin1String("LayeredWidget.h");
}
