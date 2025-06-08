#include "UnknownParameterWidget.h"
#include <QHBoxLayout>

UnknownParameterWidget::UnknownParameterWidget(QWidget* parent) :
    ParameterWidget(parent),
    m_name("Unknown parameter"),
    m_label(new QLabel("Unknown parameter:", this))
{
    QHBoxLayout* layoutControls = new QHBoxLayout(this);
    layoutControls->addWidget(m_label);
    m_label->setStyleSheet("background-color: red;");
    m_label->setToolTip(QString::number(m_label->sizeHint().width()));
}

QString UnknownParameterWidget::getName() const
{
    return m_name;
}

void UnknownParameterWidget::setName(const QString& newName)
{
    if (m_name != newName)
    {
        m_name = newName;
        m_label->setText(newName + ':');
        emit nameChanged(newName);
    }
}

int UnknownParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void UnknownParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

void UnknownParameterWidget::setFrom(const ParameterBase* parameter)
{
    setName(parameter->getName());
    setEnabled(parameter->getIsEditable());
}
