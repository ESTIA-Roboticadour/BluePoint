#ifndef LISTPARAMETERBASE_H
#define LISTPARAMETERBASE_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QVariant>

class PARAMETERS_WIDGETS_API ListParameterBase : public ParameterBase
{
    Q_OBJECT

public:
    explicit ListParameterBase(const QString& name, QObject* parent = nullptr) :
        ParameterBase(name, parent),
        m_keys(),
        m_values(),
        m_selectedIndex(-1)
    {}
    virtual ~ListParameterBase() = default;

    virtual const QStringList& getKeys() const = 0;
    virtual QVariant getSelectedValue() const = 0;
    virtual void selectValueByIndex(int index) = 0;
    int getSelectedIndex() const { return m_selectedIndex; }

    QString getSelectedKey() const
    {
        return (m_selectedIndex >= 0 && m_selectedIndex < m_keys.size()) ? m_keys[m_selectedIndex] : QString();
    }

    bool selectByKey(const QString& key) 
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

signals:
    void selectedIndexChanged(int index);

protected:
    QStringList m_keys;
    QVariantList m_values;
    int m_selectedIndex;
};

#endif // LISTPARAMETERBASE_H
