#ifndef NAVIGATIONBRANCHWIDGET_H
#define NAVIGATIONBRANCHWIDGET_H

#include "NavigationNode.h"
#include "NavigationTree.h"
#include "NavigationWidgets_global.h"

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QEvent> // pour QEvent, QEvent::DynamicPropertyChange

class NAVIGATIONWIDGETS_API NavigationBranchWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int nodeHeight     READ nodeHeight   WRITE setNodeHeight)
    Q_PROPERTY(int nodeFontSize   READ nodeFontSize WRITE setNodeFontSize)
public:
    explicit NavigationBranchWidget(QWidget* parent = nullptr);
    explicit NavigationBranchWidget(NavigationTree* tree, QWidget* parent = nullptr);
    ~NavigationBranchWidget() = default;

    NavigationTree* tree() const;
    int nodeHeight() const;
    int nodeFontSize() const;

public slots:
    void setTree(NavigationTree* tree);
    void setNodeHeight(int height);
    void setNodeFontSize(int size);
    void setTreeDef(const QString& def);

protected:
    bool event(QEvent* e) override;

private slots:
    void rebuild();
    void onButtonClicked();

private:
    void initialize();

    QFrame*      makeSeparator(QWidget* parent);
    QLabel*      makeLabel(const QString& text, QWidget* parent);
    QPushButton* makeButton(const QString& text, QWidget* parent, bool enabled);

private:
    bool m_isInitialized;
    NavigationTree* m_tree;
    int m_nodeHeight;
    int m_nodeFontSize;
    QScrollArea* m_scroll;
    QWidget* m_container;
    QVBoxLayout* m_layout;
    QString m_treeDef;
};

#endif // NAVIGATIONBRANCHWIDGET_H
