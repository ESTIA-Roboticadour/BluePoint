#include "ParametersView.h"
#include "ParametersViewPlugin.h"

#include <QtPlugin>

ParametersViewPlugin::ParametersViewPlugin(QObject *parent)
    : QObject(parent)
{
}

void ParametersViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ParametersViewPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ParametersViewPlugin::createWidget(QWidget *parent)
{
    return new ParametersView(parent);
}

QString ParametersViewPlugin::name() const
{
    return QLatin1String("ParametersView");
}

QString ParametersViewPlugin::group() const
{
    return QLatin1String("Parameters Widgets");
}

QIcon ParametersViewPlugin::icon() const
{
    return QIcon();
}

QString ParametersViewPlugin::toolTip() const
{
    return QLatin1String("Parameters View");
}

QString ParametersViewPlugin::whatsThis() const
{
    return QLatin1String("A widget that contains a vertical layout to display parameters widgets.");
}

bool ParametersViewPlugin::isContainer() const
{
    return true;
}

QString ParametersViewPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="ParametersView" name="parametersView">
    <property name="minimumSize">
        <size>
            <width>60</width>
            <height>40</height>
        </size>
    </property>
</widget>)");   
}

QString ParametersViewPlugin::includeFile() const
{
    return QLatin1String("ParametersView.h");
}
