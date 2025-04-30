#ifndef PARAMETERBASE_H
#define PARAMETERBASE_H

#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>

class PARAMETERS_WIDGETS_API ParameterBase : public QObject
{
	Q_OBJECT
public:
	explicit ParameterBase(const QString& name, QObject *parent = nullptr);
	virtual ~ParameterBase() = default;

	QString getName() const;
	bool getIsEditable() const;

public slots:
	virtual void setIsEditable(bool isEditable);
	void lock();
	void unlock();

signals:
	void isEditableChanged(bool isLocked);

private:
	QString m_name;
	bool m_isEditable;
};

#endif // PARAMETERBASE_H
