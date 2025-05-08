#ifndef NAVIGATIONBRANCHWIDGETPLUGIN_H
#define NAVIGATIONBRANCHWIDGETPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class NavigationBranchWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    explicit NavigationBranchWidgetPlugin(QObject *parent = nullptr);

    bool isContainer() const override;
    bool isInitialized() const override;
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override;
    QString includeFile() const override;
    QString name() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QWidget *createWidget(QWidget *parent) override;
    void initialize(QDesignerFormEditorInterface *core) override;

private:
    bool m_initialized = false;
};

#endif // NAVIGATIONBRANCHWIDGETPLUGIN_H
