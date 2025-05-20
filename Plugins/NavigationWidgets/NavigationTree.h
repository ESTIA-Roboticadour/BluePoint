#ifndef NAVIGATIONTREE_H
#define NAVIGATIONTREE_H

#include "NavigationNode.h"
#include "NavigationWidgets_global.h"

class NAVIGATIONWIDGETS_API NavigationTree : public QObject
{
    Q_OBJECT

public:
    explicit NavigationTree(NavigationNode* root, QObject* parent = nullptr);
    ~NavigationTree() = default;

    NavigationNode* root() const { return m_root; }
    NavigationNode* currentNode() const { return m_current; }

public slots:
    void setCurrentNode(NavigationNode* node);
    void navigateUp();
    void navigateRoot();

signals:
    void navigationRequest(NavigationNode* newNode, NavigationNode* oldNode, bool* accept);
    void currentNodeChanged(NavigationNode* node);

private:
    NavigationNode* m_root;
    NavigationNode* m_current;
};

#endif // NAVIGATIONTREE_H
