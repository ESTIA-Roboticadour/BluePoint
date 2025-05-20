#ifndef PARAMETERSVIEW_H
#define PARAMETERSVIEW_H

#include "ParametersWidgetCollection_global.h"

#include <QWidget>
#include <QLayout>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QList>

#include "ParameterBase.h"
#include "GroupParameter.h"
#include "BoolParameter.h"
#include "NumericalParameter.h"
#include "StringParameter.h"
#include "ListParameterBase.h"

class PARAMETERS_WIDGETS_API ParametersView : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(bool readonly READ isReadOnly WRITE setReadOnly NOTIFY readOnlyChanged)

public:
	explicit ParametersView(QWidget *parent = nullptr);
	~ParametersView();

	bool isReadOnly() const;

public slots:
	void setParameters(const QList<const ParameterBase*>& parameters);
	void setReadOnly(bool readonly);

private:
	static void setBoxLayoutSpacing(QBoxLayout* layout, int spacing, int left, int top, int right, int bottom);
	void clear();
	void clearLayout(QLayout* layout);
	void setParameters(const QList<const ParameterBase*>& parameters, QLayout* layout);

	QWidget* createParameterWidget(const ParameterBase* parameter);
	QWidget* createParameterGroupWidget(const GroupParameter* parameter);
	QWidget* createBoolParameterWidget(const BoolParameter* parameter) const;
	QWidget* createNumericalParameterWidget(const NumericalParameter* parameter) const;
	QWidget* createStringParameterWidget(const StringParameter* parameter) const;
	QWidget* createListParameterWidget(const ListParameterBase* parameter) const;
	QWidget* createUnknowParameterWidget(const ParameterBase* parameter) const;

signals:
	void readOnlyChanged(bool readonly);

private:
	const QList<const ParameterBase*>* m_parameters;
	bool m_isReadOnly;
	QVBoxLayout* m_layout;
};

#endif // PARAMETERSVIEW_H
