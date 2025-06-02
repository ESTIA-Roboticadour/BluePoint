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
	explicit ParametersView(QWidget *parent = nullptr);
	~ParametersView();

	bool isReadOnly() const;
    ParametersView::Alignment alignment() const;
    void clear();

public slots:
	void setParameters(const QList<const ParameterBase*>& parameters);
	void setReadOnly(bool readonly);
    void setAlignment(ParametersView::Alignment alignment);

private:
	static void setBoxLayoutSpacing(QBoxLayout* layout, int spacing, int left, int top, int right, int bottom);
	void clearLayout(QLayout* layout);
	void setParameters(const QList<const ParameterBase*>& parameters, QLayout* layout);
    void setParametersAndSetMaxWidth(const QList<const ParameterBase*>& parameters, QLayout* layout, int depth);
    int findMaxDepth(const QList<const ParameterBase*>& parameters) const;

    QWidget* createParameterWidget(const ParameterBase* parameter, int depth, int* width);
    QWidget* createParameterGroupWidget(const GroupParameter* parameter, int depth, int* width);
    QWidget* createBoolParameterWidget(const BoolParameter* parameter, int* width) const;
    QWidget* createNumericalParameterWidget(const NumericalParameter* parameter, int* width) const;
    QWidget* createStringParameterWidget(const StringParameter* parameter, int* width) const;
    QWidget* createListParameterWidget(const ListParameterBase* parameter, int* width) const;
    QWidget* createUnknowParameterWidget(const ParameterBase* parameter, int* width) const;

    void updateWidgetsAlignment();

signals:
	void readOnlyChanged(bool readonly);
    void alignmentChanged(Alignment alignment);

private:
	const QList<const ParameterBase*>* m_parameters;
	bool m_isReadOnly;
    ParametersView::Alignment m_alignment;
    QList<int> m_maxWidthPerLevel;
	QVBoxLayout* m_layout;
};

#endif // PARAMETERSVIEW_H
