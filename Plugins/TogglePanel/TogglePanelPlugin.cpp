#include "TogglePanelPlugin.h"
#include "TogglePanel.h"

#include <QtPlugin>

TogglePanelPlugin::TogglePanelPlugin(QObject *parent)
    : QObject(parent)
{}

void TogglePanelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TogglePanelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TogglePanelPlugin::createWidget(QWidget *parent)
{
    return new TogglePanel(parent);
}

QString TogglePanelPlugin::name() const
{
    return QLatin1String("TogglePanel");
}

QString TogglePanelPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon TogglePanelPlugin::icon() const
{
    return QIcon();
}

QString TogglePanelPlugin::toolTip() const
{
    return QLatin1String("Toggle Panel");
}

QString TogglePanelPlugin::whatsThis() const
{
    return QLatin1String("Panel that acts as a folding/unfolding zone using a button.");
}

bool TogglePanelPlugin::isContainer() const
{
    return true;
}

QString TogglePanelPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TogglePanel" name="togglePanel">
</widget>)");
}

QString TogglePanelPlugin::includeFile() const
{
    return QLatin1String("TogglePanel.h");
}
