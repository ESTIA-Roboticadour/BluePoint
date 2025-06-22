#include "Vector3DParameterWidget.h"

#include <QHBoxLayout>
#include <QVariant>
#include <QSizePolicy>

Vector3DParameterWidget::Vector3DParameterWidget(bool readOnly, bool canNormalize, QWidget* parent) :
    ParameterWidget(parent),
    m_readOnly(readOnly),
    m_name("Vector3D"),
    m_label(new QLabel("Vector3D:", this)),
    m_paramsLayout(new QVBoxLayout()),
    m_posSpin()
{
    for (int i = 0; i < 3; ++i) {
        m_posSpin[i] = new QDoubleSpinBox(this);
        m_posSpin[i]->setRange(-10000, 10000);
        m_posSpin[i]->setDecimals(3);
        m_posSpin[i]->setDisabled(m_readOnly);
    }
    if (!readOnly && canNormalize)
    {
        m_normalizeButton = new QPushButton("Normalize", this);
        m_normalizeButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    }

    createUI();
    connectSignals();
}

void Vector3DParameterWidget::createUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();

    mainLayout->addWidget(m_label);
    m_label->setAlignment(Qt::AlignTop);

    QString labels[3] { "X", "Y", "Z" };

    for (int i = 0; i < 3; ++i)
    {
        auto* posLabel = new QLabel(labels[i], this);
        posLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        topLayout->addWidget(posLabel);
        topLayout->addWidget(m_posSpin[i]);
    }

    m_paramsLayout->addLayout(topLayout);
    if (m_normalizeButton)
        m_paramsLayout->addWidget(m_normalizeButton);

    mainLayout->addLayout(m_paramsLayout);
}

void Vector3DParameterWidget::connectSignals()
{
    if (!m_readOnly)
    {
        connect(m_posSpin[0], &QDoubleSpinBox::valueChanged, this, &Vector3DParameterWidget::xChanged);
        connect(m_posSpin[1], &QDoubleSpinBox::valueChanged, this, &Vector3DParameterWidget::yChanged);
        connect(m_posSpin[2], &QDoubleSpinBox::valueChanged, this, &Vector3DParameterWidget::zChanged);
        if (m_normalizeButton)
            connect(m_normalizeButton, &QPushButton::clicked, this, &Vector3DParameterWidget::onNormalizeButtonClicked);
    }
}

QString Vector3DParameterWidget::getName() const { return m_name; }

void Vector3DParameterWidget::setName(const QString& newName)
{
    if (m_name != newName) {
        m_name = newName;
        m_label->setText(newName + ':');
        emit nameChanged(newName);
    }
}

QVector3D Vector3DParameterWidget::getPosition() const
{
    return QVector3D(getX(), getY(), getZ());
}

void Vector3DParameterWidget::setPosition(const QVector3D& position)
{
    m_posSpin[0]->setValue(position.x());
    m_posSpin[1]->setValue(position.y());
    m_posSpin[2]->setValue(position.z());
}

void Vector3DParameterWidget::setPosition(double x, double y, double z)
{
    m_posSpin[0]->setValue(x);
    m_posSpin[1]->setValue(y);
    m_posSpin[2]->setValue(z);
}

void Vector3DParameterWidget::setX(double value)
{
    m_posSpin[0]->setValue(value);
}

void Vector3DParameterWidget::setY(double value)
{
    m_posSpin[1]->setValue(value);
}

void Vector3DParameterWidget::setZ(double value)
{
    m_posSpin[2]->setValue(value);
}

void Vector3DParameterWidget::setCanNormalize(bool canNormalize)
{
    if (m_readOnly)
    {
        if (m_normalizeButton)
        {
            m_paramsLayout->removeWidget(m_normalizeButton);
            m_normalizeButton->deleteLater();
            m_normalizeButton = nullptr;
            emit canNormalizeChanged(canNormalize);
        }
    }
    else
    {
        if (canNormalize && !m_normalizeButton)
        {
            m_normalizeButton = new QPushButton("Normalize", this);
            m_normalizeButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            connect(m_normalizeButton, &QPushButton::clicked, this, &Vector3DParameterWidget::onNormalizeButtonClicked);
            m_paramsLayout->addWidget(m_normalizeButton);
            emit canNormalizeChanged(canNormalize);
        }
        else if (!canNormalize && m_normalizeButton)
        {
            m_paramsLayout->removeWidget(m_normalizeButton);
            m_normalizeButton->deleteLater();
            m_normalizeButton = nullptr;
            emit canNormalizeChanged(canNormalize);
        }
    }
}

int Vector3DParameterWidget::getLabelWidth() const { return m_label->sizeHint().width(); }

void Vector3DParameterWidget::setLabelWidth(int width) { m_label->setFixedWidth(width); }

void Vector3DParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly) {
        for (int i = 0; i < 3; ++i) {
            m_posSpin[i]->setEnabled(false);
        }
        if (m_normalizeButton)
            m_normalizeButton->setEnabled(false);
    }
}

void Vector3DParameterWidget::setFrom(const Vector3DParameter* parameter)
{
    setName(parameter->getName());
    QVector3D pos = parameter->getPosition();
    setX(pos.x());
    setY(pos.y());
    setZ(pos.z());
    setCanNormalize(parameter->getCanBeNormalized());
}

void Vector3DParameterWidget::onNormalizeButtonClicked()
{
    QVector3D n = getPosition().normalized();
    setX(n.x());
    setY(n.y());
    setZ(n.z());
}
