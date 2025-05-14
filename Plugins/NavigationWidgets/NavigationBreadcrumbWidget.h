#ifndef NAVIGATIONBREADCRUMBWIDGET_H
#define NAVIGATIONBREADCRUMBWIDGET_H

#include "NavigationTree.h"
#include "NavigationNode.h"
#include "NavigationWidgets_global.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QString>
#include <QEvent> // pour QEvent, QEvent::DynamicPropertyChange

class NAVIGATIONWIDGETS_API NavigationBreadcrumbWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int nodeFontSize READ nodeFontSize WRITE setNodeFontSize)
public:
    explicit NavigationBreadcrumbWidget(QWidget* parent = nullptr);
    explicit NavigationBreadcrumbWidget(NavigationTree* tree, QWidget* parent = nullptr);
    ~NavigationBreadcrumbWidget() = default;

    NavigationTree* tree() const;
    int nodeFontSize() const;

public slots:
    void setTree(NavigationTree* tree);
    void setNodeFontSize(int size);
    void setTreeDef(const QString& def);

protected:
    bool event(QEvent* e) override;

private slots:
    void rebuild();
    void onButtonClicked();

private:
    void initialize();
    QPushButton* makeButton(const QString& txt, QWidget* parent, bool enabled);
    QLabel* makeLabel(const QString& txt, QWidget* parent);
    QLabel* makeSeparator(QWidget* parent);

private:
    bool m_isInitialized;
    NavigationTree* m_tree;
    int m_nodeFontSize;
    QScrollArea* m_scrollArea;
    QWidget* m_container;
    QHBoxLayout* m_layout;
    QString m_treeDef;
};

#endif // NAVIGATIONBREADCRUMBWIDGET_H
