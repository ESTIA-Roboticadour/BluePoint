#ifndef PARAMETERSVIEW_H
#define PARAMETERSVIEW_H

#include "ParametersWidgetCollection_global.h"

#include "ParameterBase.h"
#include "GroupParameter.h"
#include "BoolParameter.h"
#include "NumericalParameter.h"
#include "StringParameter.h"
#include "ListParameterBase.h"
#include "Matrix4x4Parameter.h"
#include "EulerFrameParameter.h"
#include "Vector3DParameter.h"
#include "ParameterWidget.h"

#include <QWidget>
#include <QLayout>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QList>
#include <QStack>

typedef struct _groupInfo {
	int level = 0;
	int maxWidth = 0;
	int leftMargin = 0;
	QList<ParameterWidget*> children;
} GroupInfo;

class PARAMETERS_WIDGETS_API ParametersView : public QWidget
{
	Q_OBJECT
		Q_PROPERTY(bool readonly READ isReadOnly WRITE setReadOnly NOTIFY readOnlyChanged)
		Q_PROPERTY(ParametersView::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)
public:
	enum class Alignment
	{
		NoAlignment,
		ByGroup,
		All
	};
	Q_ENUM(Alignment)

public:
	explicit ParametersView(QWidget* parent = nullptr);
	~ParametersView();

	bool isReadOnly() const;
	ParametersView::Alignment alignment() const;
	void clear();

public slots:
	void setParameters(const QList<ParameterBase*>& parameters);
	void setParameters(const QList<const ParameterBase*>& parameters);
	void setReadOnly(bool readonly);
	void setAlignment(ParametersView::Alignment alignment);

private:
	static void setBoxLayoutSpacing(QBoxLayout* layout, int spacing, int left, int top, int right, int bottom);
	void clearLayout(QLayout* layout);
	int findMaxDepth(const QList<const ParameterBase*>& parameters) const;
	void buildUI(const QList<const ParameterBase*>& parameters);
	void buildUI(const QList<const ParameterBase*>& parameters, QLayout* layout);

	QWidget* createParameterWidget(const ParameterBase* parameter);
	QWidget* createParameterGroupWidget(const GroupParameter* parameter);
	ParameterWidget* createBoolParameterWidget(const BoolParameter* parameter);
	ParameterWidget* createNumericalParameterWidget(const NumericalParameter* parameter);
	ParameterWidget* createStringParameterWidget(const StringParameter* parameter);
	ParameterWidget* createListParameterWidget(const ListParameterBase* parameter);
    ParameterWidget* createMatrix4x4ParameterWidget(const Matrix4x4Parameter* parameter);
    ParameterWidget* createEulerFrameParameter(const EulerFrameParameter* parameter);
    ParameterWidget* createVector3DParameter(const Vector3DParameter* parameter);
	ParameterWidget* createUnknownParameterWidget(const ParameterBase* parameter);

	void createGroupInfo(const QGroupBox* groupBox);
	void feedGroupInfo(ParameterWidget* widget);
	void updateWidgetsAlignment();

signals:
	void readOnlyChanged(bool readonly);
	void alignmentChanged(Alignment alignment);

private:
	QList<const ParameterBase*> m_parameters;
	bool m_isReadOnly;
	ParametersView::Alignment m_alignment;
	QVBoxLayout* m_layout;

	// used to build the aligment
	QStack<const QGroupBox*> m_stackedGroupBoxes;
	QMap<const QGroupBox*, GroupInfo> m_groupsInfo;
};

#endif // PARAMETERSVIEW_H
