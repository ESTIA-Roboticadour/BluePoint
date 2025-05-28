#ifndef PARAMETERBASE_H
#define PARAMETERBASE_H

#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <memory>

class PARAMETERS_WIDGETS_API ParameterBase : public QObject
{
	Q_OBJECT
public:
	explicit ParameterBase(const QString& name, QObject *parent = nullptr);
	virtual ~ParameterBase() = default;

	QString getName() const;
	bool getIsEditable() const;

    virtual QJsonObject toJson() const = 0;

    static std::unique_ptr<ParameterBase> fromJson(const QJsonObject& obj, QObject* parent = nullptr);

public slots:
	virtual void setIsEditable(bool isEditable);
	void lock();
	void unlock();

signals:
    void parameterChanged(const ParameterBase* sender);
	void isEditableChanged(bool isLocked);

private:
	QString m_name;
	bool m_isEditable;
};

#endif // PARAMETERBASE_H
