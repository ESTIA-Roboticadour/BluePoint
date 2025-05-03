#include "BoolParameterWidget.h"
#include "BoolParameterWidgetPlugin.h"

#include <QtPlugin>

BoolParameterWidgetPlugin::BoolParameterWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

void BoolParameterWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BoolParameterWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BoolParameterWidgetPlugin::createWidget(QWidget *parent)
{
    return new BoolParameterWidget(parent);
}

QString BoolParameterWidgetPlugin::name() const
{
    return QLatin1String("BoolParameterWidget");
}

QString BoolParameterWidgetPlugin::group() const
{
    return QLatin1String("Parameters Widgets");
}

QIcon BoolParameterWidgetPlugin::icon() const
{
    return QIcon();
}

QString BoolParameterWidgetPlugin::toolTip() const
{
    return QLatin1String("Bool Parameter Widget");
}

QString BoolParameterWidgetPlugin::whatsThis() const
{
    return QLatin1String("A widget that contains a check box to control a boolean value.");
}

bool BoolParameterWidgetPlugin::isContainer() const
{
    return false;
}

QString BoolParameterWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="BoolParameterWidget" name="boolParameterWidget">
</widget>)");
}

QString BoolParameterWidgetPlugin::includeFile() const
{
    return QLatin1String("BoolParameterWidget.h");
}
