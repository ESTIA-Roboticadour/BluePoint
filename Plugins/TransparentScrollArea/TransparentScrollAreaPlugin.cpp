#include "TransparentScrollAreaPlugin.h"
#include "TransparentScrollArea.h"

#include <QtPlugin>

TransparentScrollAreaPlugin::TransparentScrollAreaPlugin(QObject *parent)
    : QObject(parent)
{}

void TransparentScrollAreaPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TransparentScrollAreaPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TransparentScrollAreaPlugin::createWidget(QWidget *parent)
{
    return new TransparentScrollArea(parent);
}

QString TransparentScrollAreaPlugin::name() const
{
    return QLatin1String("TransparentScrollArea");
}

QString TransparentScrollAreaPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon TransparentScrollAreaPlugin::icon() const
{
    return QIcon();
}

QString TransparentScrollAreaPlugin::toolTip() const
{
    return QLatin1String("Transparent Scroll Area");
}

QString TransparentScrollAreaPlugin::whatsThis() const
{
    return QLatin1String("A scrollable widget with a semi-transparent background, ideal for "
                         "overlay panels and modern glass-effect UIs.");
}

bool TransparentScrollAreaPlugin::isContainer() const
{
    return false;
}

QString TransparentScrollAreaPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TransparentScrollArea" name="transparentScrollArea">
</widget>)");
}

QString TransparentScrollAreaPlugin::includeFile() const
{
    return QLatin1String("TransparentScrollArea.h");
}
