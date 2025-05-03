#ifndef PARAMETERGROUP_H
#define PARAMETERGROUP_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"

#include <QObject>
#include <QString>
#include <QList>

class PARAMETERS_WIDGETS_API ParameterGroup : public ParameterBase
{
	Q_OBJECT

public:
	explicit ParameterGroup(const QString& name, QObject* parent = nullptr);
	~ParameterGroup();

	void addParameter(ParameterBase* parameter);
	void removeParameter(ParameterBase* parameter);
	void clearParameters();
	QList<const ParameterBase*> getParameters() const;

public slots:
	void setIsEditable(bool isEditable) override;

private:
	QList<ParameterBase*> m_parameters;
};

#endif // PARAMETERGROUP_H
