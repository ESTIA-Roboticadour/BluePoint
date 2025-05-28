#ifndef STRINGPARAMETERWIDGET_H
#define STRINGPARAMETERWIDGET_H

#include "StringParameter.h"
#include "ParametersWidgetCollection_global.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class PARAMETERS_WIDGETS_API StringParameterWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(StringParameter::Kind kind READ getKind WRITE setKind NOTIFY kindChanged)

public:   
	explicit StringParameterWidget(QWidget* parent = nullptr);
	~StringParameterWidget() = default;

	QString getName() const;
	QString getValue() const;
    StringParameter::Kind getKind() const;

	void setFrom(const StringParameter* parameter);

public slots:
	void setName(const QString& newName);
	void setValue(const QString& value);
    void setKind (StringParameter::Kind kind);

private slots:
	void onEditingFinished();
    void onBrowseClicked();

private:
    void updateBrowseVisibility();

signals:
	void nameChanged(const QString& name);
	void valueChanged(const QString& value);
    void kindChanged (StringParameter::Kind kind);

private:
    QString m_name;
	QLabel* m_label;
	QLineEdit* m_lineEdit;
    QPushButton* m_browseBtn;
    StringParameter::Kind m_kind;
};

#endif // STRINGPARAMETERWIDGET_H
