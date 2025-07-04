#ifndef LISTPARAMETER_H
#define LISTPARAMETER_H

#include "ListParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

template <typename T>
class ListParameter : public ListParameterBase
{
public:
    explicit ListParameter(const QString& name, QObject* parent = nullptr) :
        ListParameterBase(name, parent)
    {}

    ListParameter(const ListParameter<T>& other, QObject* parent) :
        ListParameterBase(other.getName(), parent)
    {
        m_keys          = other.m_keys;
        m_values        = other.m_values;
        m_selectedIndex = other.m_selectedIndex;
    }

    ListParameter(const QString& name, const ListParameter<T>& other, QObject* parent) :
        ListParameterBase(name, parent)
    {
        m_keys          = other.m_keys;
        m_values        = other.m_values;
        m_selectedIndex = other.m_selectedIndex;
    }

    ~ListParameter() override = default;

    ParameterBase* copy(QObject* parent = nullptr) const override
    {
        return new ListParameter<T>(*this, parent);
    }

    bool addItem(const QString& key, const T& value)
    {
        int i;
        for (i = 0; i < m_keys.size(); i++)
        {
            if (m_keys[i] == key)
            {
                break;
            }
        }
        bool added = i == m_keys.size();
        if (added)
        {
            m_keys.append(key);
            m_values.append(QVariant::fromValue(value));
            if (m_selectedIndex == -1)
            {
                selectValueByIndex(0);
            }
        }

        return added;
    }

    QVariant getSelectedValue() const override
    {
        return (m_selectedIndex >= 0 && m_selectedIndex < m_values.size()) ?
                   m_values[m_selectedIndex] :
                   QVariant();
    }

    T getSelectedTypedValue() const
    {
        return (m_selectedIndex >= 0 && m_selectedIndex < m_values.size()) ?
                   m_values[m_selectedIndex].value<T>() :
                   T();
    }

    void selectValueByIndex(int index) override
    {
        if (index >= 0 && index < m_values.size() && index != m_selectedIndex)
        {
            m_selectedIndex = index;
            emit selectedIndexChanged(m_selectedIndex);
            emit parameterChanged(this);
        }
    }

    void selectValue(const T& value)
    {
        for (int i = 0; i < m_values.size(); i++)
        {
            if (m_values[i].value<T>() == value)
            {
                selectValueByIndex(i);
            }
        }
    }
};

#endif // LISTPARAMETER_H
