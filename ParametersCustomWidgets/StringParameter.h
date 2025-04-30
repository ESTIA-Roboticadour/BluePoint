#ifndef STRINGPARAMETER_H
#define STRINGPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>

class PARAMETERS_WIDGETS_API StringParameter : public ParameterBase
{
	Q_OBJECT

public:
	explicit StringParameter(const QString& name, const QString& value="", QObject* parent = nullptr);
	~StringParameter() = default;

	QString getValue() const;

public slots:
	void setValue(const QString& value);

signals:
	void valueChanged(const QString& value);

private:
	QString m_value;
};

#endif // STRINGPARAMETER_H
