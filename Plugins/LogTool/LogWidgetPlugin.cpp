#include "LogWidgetPlugin.h"
#include "LogWidget.h"

#include <QtPlugin>

LogWidgetPlugin::LogWidgetPlugin(QObject *parent)
    : QObject(parent)
{}

void LogWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LogWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LogWidgetPlugin::createWidget(QWidget *parent)
{
    return new LogWidget(parent);
}

QString LogWidgetPlugin::name() const
{
    return QLatin1String("LogWidget");
}

QString LogWidgetPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon LogWidgetPlugin::icon() const
{
    return QIcon();
}

QString LogWidgetPlugin::toolTip() const
{
    return QLatin1String("Real-time log table");
}

QString LogWidgetPlugin::whatsThis() const
{
    return QLatin1String("Displays and colours messages from qDebug/qInfo/...");
}

bool LogWidgetPlugin::isContainer() const
{
    return false;
}

QString LogWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="LogWidget" name="logWidget">
</widget>)");
}

QString LogWidgetPlugin::includeFile() const
{
    return QLatin1String("LogWidget.h");
}
