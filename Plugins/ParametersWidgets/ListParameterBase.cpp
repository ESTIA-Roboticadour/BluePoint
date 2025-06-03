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

const QStringList& ListParameterBase::getKeys() const
{
    return m_keys;
}

const QVariantList& ListParameterBase::getValues() const
{
    return m_values;
}

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
        emit parameterChanged(this);
        return true;
    }
    return false;
}

bool ListParameterBase::containsKey(const QString& key) const
{
    return m_keys.contains(key);
}

int ListParameterBase::indexOfKey(const QString& key) const
{
    return m_keys.indexOf(key);
}

bool ListParameterBase::containsValue(const QVariant& value) const
{
    return m_values.contains(value);
}

int ListParameterBase::indexOfValue(const QVariant& value) const
{
    return m_values.indexOf(value);
}

QList<QPair<QString, QVariant>> ListParameterBase::items() const
{
    QList<QPair<QString, QVariant>> out;
    out.reserve(m_keys.size());
    for (int i = 0; i < m_keys.size() && i < m_values.size(); ++i)
        out.append(qMakePair(m_keys[i], m_values[i]));
    return out;
}

void ListParameterBase::clear()
{
    m_keys.clear();
    m_values.clear();
    m_selectedIndex = -1;
    emit parameterChanged(this);
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
