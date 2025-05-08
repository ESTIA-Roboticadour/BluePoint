#include "NavigationTree.h"

NavigationTree::NavigationTree(NavigationNode* rootNode, QObject* parent) :
    QObject(parent),
    m_root(rootNode),
    m_current(rootNode)
{
    Q_ASSERT(rootNode);
    m_root->setSelected(true);
}

void NavigationTree::setCurrentNode(NavigationNode* node)
{
    if (!node || node == m_current)
        return;

    if (m_current)
        m_current->setSelected(false);

    m_current = node;
    m_current->setSelected(true);

    emit currentNodeChanged(m_current);
}

void NavigationTree::navigateUp()
{
    if (m_current && m_current->parentNode())
    {
        setCurrentNode(m_current->parentNode());
    }
}

void NavigationTree::navigateRoot()
{
    setCurrentNode(m_root);
}
