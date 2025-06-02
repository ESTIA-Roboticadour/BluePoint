#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QWidget>

class ParameterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParameterWidget(QWidget *parent = nullptr);

    virtual int getLabelWidth() const = 0;

public slots:
    virtual void setLabelWidth(int width) = 0;
};

#endif // PARAMETERWIDGET_H
