#include "LogoWidgetPlugin.h"
#include "LogoWidget.h"

#include <QtPlugin>

LogoWidgetPlugin::LogoWidgetPlugin(QObject *parent)
    : QObject(parent)
{}

void LogoWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LogoWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LogoWidgetPlugin::createWidget(QWidget *parent)
{
    return new LogoWidget(parent);
}

QString LogoWidgetPlugin::name() const
{
    return QLatin1String("LogoWidget");
}

QString LogoWidgetPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon LogoWidgetPlugin::icon() const
{
    return QIcon();
}

QString LogoWidgetPlugin::toolTip() const
{
    return QLatin1String("Displays a resizable logo");
}

QString LogoWidgetPlugin::whatsThis() const
{
    return QLatin1String("Widget contenant un QLabel avec pixmap redimensionnable");
}

bool LogoWidgetPlugin::isContainer() const
{
    return false;
}

QString LogoWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="LogoWidget" name="logoWidget">
</widget>)");
}

QString LogoWidgetPlugin::includeFile() const
{
    return QLatin1String("LogoWidget.h");
}
