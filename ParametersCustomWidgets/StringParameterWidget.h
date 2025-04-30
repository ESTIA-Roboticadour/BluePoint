#ifndef STRINGPARAMETERWIDGET_H
#define STRINGPARAMETERWIDGET_H

#include "StringParameter.h"
#include "ParametersWidgetCollection_global.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>

class PARAMETERS_WIDGETS_API StringParameterWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)

public:
	explicit StringParameterWidget(QWidget* parent = nullptr);
	~StringParameterWidget() = default;

	QString getName() const;
	QString getValue() const;

	void setFrom(const StringParameter* parameter);

public slots:
	void setName(const QString& newName);
	void setValue(const QString& value);

private slots:
	void onEditingFinished();

signals:
	void nameChanged(const QString& name);
	void valueChanged(const QString& value);

private:
	QLabel* m_label;
	QLineEdit* m_lineEdit;
	QString m_name;
};

#endif // STRINGPARAMETERWIDGET_H
