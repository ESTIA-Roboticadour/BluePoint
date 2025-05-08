#ifndef NAVIGATIONWIDGETSCOLLECTIONPLUGIN_H
#define NAVIGATIONWIDGETSCOLLECTIONPLUGIN_H

#include <QtDesigner>
#include <qplugin.h>

class NavigationWidgetsCollectionPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")

public:
    explicit NavigationWidgetsCollectionPlugin(QObject *parent = nullptr);

    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif // NAVIGATIONWIDGETSCOLLECTIONPLUGIN_H
