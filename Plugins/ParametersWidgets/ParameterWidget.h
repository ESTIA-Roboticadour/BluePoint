#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include "ParametersWidgetCollection_global.h"
#include <QWidget>

class PARAMETERS_WIDGETS_API ParameterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParameterWidget(QWidget *parent = nullptr);

    virtual int getLabelWidth() const = 0;

public slots:
    virtual void setLabelWidth(int width) = 0;
};

#endif // PARAMETERWIDGET_H
