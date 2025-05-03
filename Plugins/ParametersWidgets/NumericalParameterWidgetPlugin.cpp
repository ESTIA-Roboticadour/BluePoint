#include "NumericalParameterWidget.h"
#include "NumericalParameterWidgetPlugin.h"

#include <QtPlugin>

NumericalParameterWidgetPlugin::NumericalParameterWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

void NumericalParameterWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NumericalParameterWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NumericalParameterWidgetPlugin::createWidget(QWidget *parent)
{
    return new NumericalParameterWidget(parent);
}

QString NumericalParameterWidgetPlugin::name() const
{
    return QLatin1String("NumericalParameterWidget");
}

QString NumericalParameterWidgetPlugin::group() const
{
    return QLatin1String("Parameters Widgets");
}

QIcon NumericalParameterWidgetPlugin::icon() const
{
    return QIcon();
}

QString NumericalParameterWidgetPlugin::toolTip() const
{
    return QLatin1String("Numerical Parameter Widget");
}

QString NumericalParameterWidgetPlugin::whatsThis() const
{
    return QLatin1String("A widget that contains a label, a slider and a spin box to control a numerical value.");
}

bool NumericalParameterWidgetPlugin::isContainer() const
{
    return false;
}

QString NumericalParameterWidgetPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="NumericalParameterWidget" name="numericalParameterWidget">
</widget>)");
}

QString NumericalParameterWidgetPlugin::includeFile() const
{
    return QLatin1String("NumericalParameterWidget.h");
}
