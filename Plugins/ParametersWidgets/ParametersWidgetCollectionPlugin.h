#ifndef PARAMETERSWIDGETCOLLECTIONPLUGIN_H
#define PARAMETERSWIDGETCOLLECTIONPLUGIN_H

#include <QObject>
#include <QtDesigner>
#include <qplugin.h>

class ParametersWidgetCollection : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")

public:
    explicit ParametersWidgetCollection(QObject *parent = nullptr);

    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif // PARAMETERSWIDGETCOLLECTIONPLUGIN_H
