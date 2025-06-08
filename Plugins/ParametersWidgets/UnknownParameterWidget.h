#ifndef UNKNOWNPARAMETERWIDGET_H
#define UNKNOWNPARAMETERWIDGET_H

#include "ParameterBase.h"
#include "ParametersWidgetCollection_global.h"
#include "ParameterWidget.h"

#include <QWidget>
#include <QString>
#include <QLabel>

class PARAMETERS_WIDGETS_API UnknownParameterWidget : public ParameterWidget
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
    explicit UnknownParameterWidget(QWidget* parent = nullptr);
    ~UnknownParameterWidget() = default;

    QString getName() const;
    int getLabelWidth() const override;

    void setFrom(const ParameterBase* parameter);

public slots:
    void setName(const QString& newName);
    void setLabelWidth(int width) override;

signals:
    void nameChanged(const QString& name);

private:
    QString m_name;
    QLabel* m_label;
};

#endif // UNKNOWNPARAMETERWIDGET_H
