#ifndef BOOLPARAMETERWIDGET_H
#define BOOLPARAMETERWIDGET_H

#include "BoolParameter.h"
#include "ParametersWidgetCollection_global.h"
#include "ParameterWidget.h"

#include <QWidget>
#include <QString>
#include <QCheckBox>
#include <QLabel>

class PARAMETERS_WIDGETS_API BoolParameterWidget : public ParameterWidget
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged)

public:
    explicit BoolParameterWidget(bool readOnly = false, QWidget* parent = nullptr);
	~BoolParameterWidget() = default;

	QString getName() const;
	bool getValue() const;

    int getLabelWidth() const override;

	void setFrom(const BoolParameter* parameter);

public slots:
	void setName(const QString& newName);
	void setValue(bool value);
    void setLabelWidth(int width) override;
    void setEnabled(bool enabled);

signals:
	void nameChanged(const QString& name);
	void valueChanged(bool value);

private:
    QString m_name;
    QLabel* m_label;
	QCheckBox* m_checkBox;
    bool m_readOnly;
};

#endif // BOOLPARAMETERWIDGET_H
