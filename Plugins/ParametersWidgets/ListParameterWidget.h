#ifndef LISTPARAMETERWIDGET_H
#define LISTPARAMETERWIDGET_H

#include "ListParameterBase.h"
#include "ParametersWidgetCollection_global.h"
#include "ParameterWidget.h"

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

class PARAMETERS_WIDGETS_API ListParameterWidget : public ParameterWidget
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList options READ getOptions WRITE setOptions NOTIFY optionsChanged)
	Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex NOTIFY selectedIndexChanged)

public:
    explicit ListParameterWidget(bool readOnly = false, QWidget* parent = nullptr);
	~ListParameterWidget() override = default;

	QString getName() const;
	QStringList getOptions() const;
	int getCurrentIndex() const;
    int getLabelWidth() const override;

	void setFrom(const ListParameterBase* parameter);

public slots:
	void setName(const QString& name);
	void setOptions(const QStringList& keys);
	void setCurrentIndex(int index);
    void setLabelWidth(int width) override;
    void setEnabled(bool enabled);

signals:
	void nameChanged(const QString& name);
    void optionsChanged(const QStringList& options);
	void selectedIndexChanged(int index);

private:
	QLabel* m_label;
	QComboBox* m_comboBox;
	QString m_name;
    QLineEdit* m_lineEdit;
    QStringList m_options;
    int m_selectedIndex;
    bool m_readOnly;
};

#endif // LISTPARAMETERWIDGET_H
