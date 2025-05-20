#include "ListParameterBase.h"
#include "ListParameter.h"
#include <QJsonValue>
#include <QJsonArray>

ListParameterBase::ListParameterBase(const QString& name, QObject* parent) :
    ParameterBase(name, parent),
    m_keys(),
    m_values(),
    m_selectedIndex(-1)
{}

int ListParameterBase::getSelectedIndex() const
{
    return m_selectedIndex;
}

QString ListParameterBase::getSelectedKey() const
{
    return (m_selectedIndex >= 0 && m_selectedIndex < m_keys.size()) ? m_keys[m_selectedIndex] : QString();
}

bool ListParameterBase::selectByKey(const QString& key)
{
    int index = m_keys.indexOf(key);
    if (index != -1 && index != m_selectedIndex)
    {
        m_selectedIndex = index;
        emit selectedIndexChanged(index);
        return true;
    }
    return false;
}

QJsonObject ListParameterBase::toJson() const
{
    QJsonArray kArr, vArr;
    for (int i = 0; i < m_keys.size(); ++i) {
        kArr.append(m_keys[i]);
        vArr.append(QJsonValue::fromVariant(m_values[i]));
    }
    return {{"type",   "list"},
            {"name",   getName()},
            {"keys",   kArr},
            {"values", vArr},
            {"index",  m_selectedIndex}};
}

std::unique_ptr<ParameterBase> ListParameterBase::fromJson(const QJsonObject& o, QObject* parent)
{
    auto lp = std::make_unique<ListParameter<QVariant>>(o["name"].toString(), parent);

    const QJsonArray keys   = o["keys"].toArray();
    const QJsonArray values = o["values"].toArray();
    const int n = std::min(keys.size(), values.size());
    for (int i = 0; i < n; ++i)
        lp->addItem(keys[i].toString(), values[i].toVariant());
    lp->selectValueByIndex(o["index"].toInt(-1));
    return lp;
}
