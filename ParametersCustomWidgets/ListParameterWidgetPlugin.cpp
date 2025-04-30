#include "ListParameterWidget.h"
#include "ListParameterWidgetPlugin.h"

#include <QtPlugin>

ListParameterWidgetPlugin::ListParameterWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

void ListParameterWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ListParameterWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ListParameterWidgetPlugin::createWidget(QWidget *parent)
{
    return new ListParameterWidget(parent);
}

QString ListParameterWidgetPlugin::name() const
{
    return QLatin1String("ListParameterWidget");
}

QString ListParameterWidgetPlugin::group() const
{
    return QLatin1String("Parameters Widgets");
}

QIcon ListParameterWidgetPlugin::icon() const
{
    return QIcon();
}

QString ListParameterWidgetPlugin::toolTip() const
{
    return QLatin1String("List Parameter Widget");
}

QString ListParameterWidgetPlugin::whatsThis() const
{
    return QLatin1String("A widget that contains a label and a bombo box to control a boolean value.");
}

bool ListParameterWidgetPlugin::isContainer() const
{
    return false;
}

QString ListParameterWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="ListParameterWidget" name="listParameterWidget">
</widget>)");
}

QString ListParameterWidgetPlugin::includeFile() const
{
    return QLatin1String("ListParameterWidget.h");
}
