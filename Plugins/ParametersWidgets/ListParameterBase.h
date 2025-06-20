#ifndef LISTPARAMETERBASE_H
#define LISTPARAMETERBASE_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QVariant>
#include <QJsonObject>
#include <QPair>
#include <QList>
#include <memory>

class PARAMETERS_WIDGETS_API ListParameterBase : public ParameterBase
{
    Q_OBJECT
public:
    explicit ListParameterBase(const QString& name, QObject* parent = nullptr);
    virtual ~ListParameterBase() = default;

    const QStringList& getKeys() const;
    const QVariantList& getValues() const;

    virtual QVariant getSelectedValue() const = 0;
    virtual void selectValueByIndex(int index) = 0;

    int getSelectedIndex() const;
    QString getSelectedKey() const;
    bool selectByKey(const QString& key);

    bool containsKey(const QString& key) const;
    int indexOfKey(const QString& key) const;

    bool containsValue(const QVariant& value) const;
    int indexOfValue(const QVariant& value) const;

    QList<QPair<QString, QVariant>> items() const;
    void clear();

    QJsonObject toJson() const override;
    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

signals:
    void selectedIndexChanged(int index);

protected:
    QStringList m_keys;
    QVariantList m_values;
    int m_selectedIndex;
};

#endif // LISTPARAMETERBASE_H
