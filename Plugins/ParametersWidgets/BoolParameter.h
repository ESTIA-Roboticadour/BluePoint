#ifndef BOOLPARAMETER_H
#define BOOLPARAMETER_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>

class PARAMETERS_WIDGETS_API BoolParameter : public ParameterBase
{
	Q_OBJECT

public:
	explicit BoolParameter(const QString& name, const bool value = false, QObject* parent = nullptr);
	~BoolParameter() = default;

	bool getValue() const;

public slots:
	void setValue(bool value);

signals:
	void valueChanged(bool value);

private:
	bool m_value;
};

#endif // BOOLPARAMETER_H
