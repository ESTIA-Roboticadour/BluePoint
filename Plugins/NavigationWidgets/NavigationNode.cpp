#include "NavigationNode.h"

NavigationNode::NavigationNode(const QString& name, NavigationNode* parentNode, QObject* parent) :
    QObject(parent),
    m_name(name),
    m_selected(false),
    m_parent(parentNode),
    m_children()
{
    if (m_parent)
        m_parent->addChild(this);
}

NavigationNode* NavigationNode::createChild(const QString& name)
{
    return addChild(new NavigationNode(name, nullptr, this));
}

NavigationNode* NavigationNode::addChild(NavigationNode* child)
{
    if (child && child->m_parent != this)
    {
        if (child->m_parent)
        {
            child->m_parent->removeChild(child);
        }
        child->m_parent = this;
        if (!m_children.contains(child))
        {
            m_children.push_back(child);
            emit nodeChanged(this);
        }
    }
    return child;
}

NavigationNode* NavigationNode::getChild(int index) const
{
    NavigationNode* node = nullptr;
    if (index >= 0 && index < m_children.size())
    {
        node = m_children[index];
    }
    return node;
}

NavigationNode* NavigationNode::getChild(const QString& name) const
{
    for (auto* child : m_children)
    {
        if (child->m_name == name)
            return child;
    }
    return nullptr;
}

bool NavigationNode::removeChild(NavigationNode* child)
{
    return child ? removeChild(m_children.indexOf(child)) : false;
}

bool NavigationNode::removeChild(const QString& name)
{
    return removeChild(getChild(name));
}

bool NavigationNode::removeChild(int index)
{
    bool deleted = false;
    if (index >= 0 && index < m_children.size())
    {
        m_children[index]->m_parent = nullptr;
        m_children.remove(index);
        deleted = true;
        emit nodeChanged(this);
    }
    return deleted;
}

void NavigationNode::setName(const QString& name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nodeChanged(this);
    }
}

void NavigationNode::setSelected(bool selected)
{
    if (m_selected != selected)
    {
        m_selected = selected;
        emit selectionChanged(this, m_selected);
    }
}

bool NavigationNode::containsSelectedDescendant() const
{
    if (m_selected)
        return true;
    for (const auto* child : m_children) {
        if (child->containsSelectedDescendant())
            return true;
    }
    return false;
}

QStringList NavigationNode::path() const
{
    QStringList segments;
    const NavigationNode* iter = this;
    while (iter) {
        segments.prepend(iter->m_name);
        iter = iter->m_parent;
    }
    return segments;
}

QList<const NavigationNode*> NavigationNode::pathNodes() const
{
    QList<const NavigationNode*> segments;
    const NavigationNode* iter = this;
    while (iter) {
        segments.prepend(iter);
        iter = iter->m_parent;
    }
    return segments;
}
