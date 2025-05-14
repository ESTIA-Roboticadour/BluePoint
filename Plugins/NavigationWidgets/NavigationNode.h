#ifndef NAVIGATIONNODE_H
#define NAVIGATIONNODE_H

#include "NavigationWidgets_global.h"

#include <QObject>
#include <QVector>
#include <QString>
#include <QList>
#include <QStringList>

class NAVIGATIONWIDGETS_API NavigationNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
public:
    explicit NavigationNode(const QString& name, NavigationNode* parentNode = nullptr, QObject* parent = nullptr);
    ~NavigationNode() = default;

    NavigationNode* parentNode() const { return m_parent; }
    const QVector<NavigationNode*>& children() const { return m_children; }

    NavigationNode* createChild(const QString& name);
    NavigationNode* addChild(NavigationNode* child);

    NavigationNode* getChild(int index) const;
    NavigationNode* getChild(const QString& name) const;

    bool removeChild(int index);
    bool removeChild(NavigationNode* child);
    bool removeChild(const QString& name);

    bool hasParent() const { return m_parent != nullptr; }
    bool hasChildren() const { return !m_children.isEmpty(); }

    QString name() const { return m_name; }
    bool isSelected() const { return m_selected; }
    bool isEnabled() const { return m_enabled; }

    bool containsSelectedDescendant() const;

    QStringList path() const;
    QList<const NavigationNode*> pathNodes() const;

public slots:
    void setName(const QString& name);
    void setSelected(bool selected);
    void setEnabled(bool enabled);

signals:
    void selectionChanged(NavigationNode* node, bool selected);
    void enabledChanged(NavigationNode* node, bool enabled);
    void nodeChanged(NavigationNode* node);

private:
    QString m_name;
    bool m_selected;
    bool m_enabled;
    NavigationNode* m_parent;
    QVector<NavigationNode*> m_children;
};

#endif // NAVIGATIONNODE_H
