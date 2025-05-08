#include "NavigationBranchWidget.h"
#include "NavigationBranchWidgetPlugin.h"

#include <QtPlugin>

NavigationBranchWidgetPlugin::NavigationBranchWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

void NavigationBranchWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NavigationBranchWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NavigationBranchWidgetPlugin::createWidget(QWidget *parent)
{
    return new NavigationBranchWidget(parent);
}

QString NavigationBranchWidgetPlugin::name() const
{
    return QLatin1String("NavigationBranchWidget");
}

QString NavigationBranchWidgetPlugin::group() const
{
    return QLatin1String("Navigation Widgets");
}

QIcon NavigationBranchWidgetPlugin::icon() const
{
    return QIcon();
}

QString NavigationBranchWidgetPlugin::toolTip() const
{
    return QLatin1String("Navigation Branch Widget");
}

QString NavigationBranchWidgetPlugin::whatsThis() const
{
    return QLatin1String("A vertical, scrollable list that shows the children of the current navigation node — or, when the node has no children, its siblings. It includes an optional “parent” shortcut and emits clicks that update a NavigationTree. Ideal for sidebar menus.");
}

bool NavigationBranchWidgetPlugin::isContainer() const
{
    return false;
}

QString NavigationBranchWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="NavigationBranchWidget" name="navigationBranchWidget">
    <property name="minimumSize">
        <size>
            <width>60</width>
            <height>40</height>
        </size>
    </property>
</widget>)");
}

QString NavigationBranchWidgetPlugin::includeFile() const
{
    return QLatin1String("NavigationBranchWidget.h");
}
