#include "FrameViewerPlugin.h"
#include "FrameViewer.h"

#include <QtPlugin>

FrameViewerPlugin::FrameViewerPlugin(QObject *parent)
    : QObject(parent)
{}

void FrameViewerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FrameViewerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FrameViewerPlugin::createWidget(QWidget *parent)
{
    return new FrameViewer(parent);
}

QString FrameViewerPlugin::name() const
{
    return QLatin1String("FrameViewer");
}

QString FrameViewerPlugin::group() const
{
    return QLatin1String("Custom Widgets");
}

QIcon FrameViewerPlugin::icon() const
{
    return QIcon();
}

QString FrameViewerPlugin::toolTip() const
{
    return QLatin1String("Frame Viewer");
}

QString FrameViewerPlugin::whatsThis() const
{
    return QLatin1String("A frame viewer");
}

bool FrameViewerPlugin::isContainer() const
{
    return false;
}

QString FrameViewerPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="FrameViewer" name="frameViewer">
</widget>)");
}

QString FrameViewerPlugin::includeFile() const
{
    return QLatin1String("FrameViewer.h");
}
