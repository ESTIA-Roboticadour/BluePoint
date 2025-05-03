#ifndef BOOLPARAMETERWIDGET_H
#define BOOLPARAMETERWIDGET_H

#include "BoolParameter.h"
#include "ParametersWidgetCollection_global.h"

#include <QWidget>
#include <QString>
#include <QCheckBox>

class PARAMETERS_WIDGETS_API BoolParameterWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged)

public:
	explicit BoolParameterWidget(QWidget* parent = nullptr);
	~BoolParameterWidget() = default;

	QString getName() const;
	bool getValue() const;

	void setFrom(const BoolParameter* parameter);

public slots:
	void setName(const QString& newName);
	void setValue(bool value);

signals:
	void nameChanged(const QString& name);
	void valueChanged(bool value);

private:
	QCheckBox* m_checkBox;
};

#endif // BOOLPARAMETERWIDGET_H
