#include "StringParameterWidget.h"
#include "StringParameterWidgetPlugin.h"

#include <QtPlugin>

StringParameterWidgetPlugin::StringParameterWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

void StringParameterWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool StringParameterWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *StringParameterWidgetPlugin::createWidget(QWidget *parent)
{
    return new StringParameterWidget(parent);
}

QString StringParameterWidgetPlugin::name() const
{
    return QLatin1String("StringParameterWidget");
}

QString StringParameterWidgetPlugin::group() const
{
    return QLatin1String("Parameters Widgets");
}

QIcon StringParameterWidgetPlugin::icon() const
{
    return QIcon();
}

QString StringParameterWidgetPlugin::toolTip() const
{
    return QLatin1String("String Parameter Widget");
}

QString StringParameterWidgetPlugin::whatsThis() const
{
    return QLatin1String("A widget that contains a label and a text input to control a boolean value.");
}

bool StringParameterWidgetPlugin::isContainer() const
{
    return false;
}

QString StringParameterWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="StringParameterWidget" name="stringParameterWidget">
</widget>)");
}

QString StringParameterWidgetPlugin::includeFile() const
{
    return QLatin1String("StringParameterWidget.h");
}
