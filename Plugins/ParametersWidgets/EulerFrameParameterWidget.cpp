#include "EulerFrameParameterWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVariant>

EulerFrameParameterWidget::EulerFrameParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
    m_readOnly(readOnly),
    m_x(0.),
    m_y(0.),
    m_z(0.),
    m_a(0.),
    m_b(0.),
    m_c(0.),
    m_name("Euler Frame"),
    m_label(new QLabel("Euler Frame:", this)),
    m_comboBox(new QComboBox(this)),
    m_isSliderUpdating(false),
    m_convention(EulerFrameParameter::Convention::XYZ)
{
    for (const auto& convention : EulerFrameParameter::getConventions()) {

        m_comboBox->addItem(EulerFrameParameter::toQString(convention), QVariant::fromValue(convention));
    }

    m_comboBox->setDisabled(m_readOnly);
    m_comboBox->setFixedWidth(60);

    for (int i = 0; i < 3; ++i) {
        m_posSpin[i] = new QDoubleSpinBox(this);
        m_posSpin[i]->setRange(-10000, 10000);
        m_posSpin[i]->setDecimals(3);
        m_posSpin[i]->setDisabled(m_readOnly);

        m_angleSpin[i] = new QDoubleSpinBox(this);
        m_angleSpin[i]->setRange(-180.0, 180.0);
        m_angleSpin[i]->setDecimals(3);
        m_angleSpin[i]->setDisabled(m_readOnly);

        if (m_readOnly)
        {
            m_angleSlider[i] = nullptr;
        }
        else
        {
            m_angleSlider[i] = new QSlider(Qt::Horizontal, this);
            m_angleSlider[i]->setRange(-180, 180);
            m_angleSlider[i]->setVisible(!m_readOnly);
        }
    }

    createUI();
    connectSignals();
}

void EulerFrameParameterWidget::createUI()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* labelLayout = new QVBoxLayout();
    QVBoxLayout* paramsLayout = new QVBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();

    labelLayout->addWidget(m_label);
    labelLayout->addStretch();

    auto* label = new QLabel("Convention:", this);
    topLayout->addWidget(label);
    topLayout->addWidget(m_comboBox);
    topLayout->addStretch();

    QGridLayout* grid = new QGridLayout();
    QString labels[6] { "X", "Y", "Z", "A", "B", "C" };

    for (int i = 0; i < 3; ++i)
    {
        auto* posLayout = new QHBoxLayout();
        auto* posLabel = new QLabel(labels[i], this);
        posLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        posLayout->addWidget(posLabel);
        posLayout->addWidget(m_posSpin[i]);
        grid->addLayout(posLayout, 0, i);

        auto* angLayout = new QHBoxLayout();
        auto* angLabel = new QLabel(labels[3 + i], this);
        angLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        angLayout->addWidget(angLabel);
        angLayout->addWidget(m_angleSpin[i]);
        grid->addLayout(angLayout, 1, i);

        if (m_angleSlider[i])
        {
            auto* slidLayout = new QHBoxLayout();
            auto* slidLabel = new QLabel("   ", this);
            slidLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
            slidLayout->addWidget(slidLabel);
            slidLayout->addWidget(m_angleSlider[i]);
            grid->addLayout(slidLayout, 2, i);
        }
    }

    paramsLayout->addLayout(topLayout);
    paramsLayout->addLayout(grid);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(paramsLayout);
}

void EulerFrameParameterWidget::connectSignals()
{
    if (!m_readOnly)
    {
        connect(m_posSpin[0], &QDoubleSpinBox::valueChanged, this, &EulerFrameParameterWidget::xChanged);
        connect(m_posSpin[1], &QDoubleSpinBox::valueChanged, this, &EulerFrameParameterWidget::yChanged);
        connect(m_posSpin[2], &QDoubleSpinBox::valueChanged, this, &EulerFrameParameterWidget::zChanged);

        connect(m_angleSpin[0], &QDoubleSpinBox::valueChanged, this, [this](double value) { onSpinBoxValueChanged(0, value); });
        connect(m_angleSpin[1], &QDoubleSpinBox::valueChanged, this, [this](double value) { onSpinBoxValueChanged(1, value); });
        connect(m_angleSpin[2], &QDoubleSpinBox::valueChanged, this, [this](double value) { onSpinBoxValueChanged(2, value); });

        connect(m_angleSlider[0], &QSlider::valueChanged, this, [this](int value) { onSliderValueChanged(0, value); });
        connect(m_angleSlider[1], &QSlider::valueChanged, this, [this](int value) { onSliderValueChanged(1, value); });
        connect(m_angleSlider[2], &QSlider::valueChanged, this, [this](int value) { onSliderValueChanged(2, value); });

        connect(m_comboBox, &QComboBox::currentIndexChanged, this, &EulerFrameParameterWidget::onConventionChanged);
    }
}

QString EulerFrameParameterWidget::getName() const { return m_name; }

void EulerFrameParameterWidget::setName(const QString& newName)
{
    if (m_name != newName) {
        m_name = newName;
        m_label->setText(newName + ':');
        emit nameChanged(newName);
    }
}

EulerFrameParameter::Convention EulerFrameParameterWidget::getConvention() const
{
    return m_convention;
}

void EulerFrameParameterWidget::setConvention(EulerFrameParameter::Convention convention)
{
    for (int i = 0; i < m_comboBox->count(); ++i) {
        QVariant data = m_comboBox->itemData(i);

        EulerFrameParameter::Convention itemConvention = data.value<EulerFrameParameter::Convention>();
        if (itemConvention == convention) {
            m_comboBox->setCurrentIndex(i);
            return;
        }
    }
}

QVector3D EulerFrameParameterWidget::getPosition() const
{
    return QVector3D(m_x, m_y, m_z);
}

QVector3D EulerFrameParameterWidget::getAngles() const
{
    return QVector3D(m_a, m_b, m_c);
}

void EulerFrameParameterWidget::setPosition(const QVector3D& position)
{
    m_posSpin[0]->setValue(position.x());
    m_posSpin[1]->setValue(position.y());
    m_posSpin[2]->setValue(position.z());
}

void EulerFrameParameterWidget::setAngles(const QVector3D& angles)
{
    m_angleSpin[0]->setValue(angles.x());
    m_angleSpin[1]->setValue(angles.y());
    m_angleSpin[2]->setValue(angles.z());
}

void EulerFrameParameterWidget::setX(double value)
{
    m_posSpin[0]->setValue(value);
}

void EulerFrameParameterWidget::setY(double value)
{
    m_posSpin[1]->setValue(value);
}

void EulerFrameParameterWidget::setZ(double value)
{
    m_posSpin[2]->setValue(value);
}

void EulerFrameParameterWidget::setA(double value)
{
    m_angleSpin[0]->setValue(value);
}

void EulerFrameParameterWidget::setB(double value)
{
    m_angleSpin[1]->setValue(value);
}

void EulerFrameParameterWidget::setC(double value)
{
    m_angleSpin[2]->setValue(value);
}

int EulerFrameParameterWidget::getLabelWidth() const { return m_label->sizeHint().width(); }

void EulerFrameParameterWidget::setLabelWidth(int width) { m_label->setFixedWidth(width); }

void EulerFrameParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly) {
        for (int i = 0; i < 3; ++i) {
            m_posSpin[i]->setEnabled(false);
            m_angleSpin[i]->setEnabled(false);
        }
        m_comboBox->setEnabled(false);
    }
}

void EulerFrameParameterWidget::setFrom(const EulerFrameParameter* parameter)
{
    setName(parameter->getName());
    QVector3D pos = parameter->getPosition();
    QVector3D ang = parameter->getAngles();

    m_comboBox->setCurrentIndex(static_cast<int>(parameter->getConvention()));
    for (int i = 0; i < 3; ++i) {
        m_posSpin[i]->setValue(pos[i]);
        m_angleSpin[i]->setValue(ang[i]);
    } 
    setEnabled(parameter->getIsEditable());
}

void EulerFrameParameterWidget::onConventionChanged(int selectedIndex)
{
    Q_UNUSED(selectedIndex)
    EulerFrameParameter::Convention convention = m_comboBox->currentData().value<EulerFrameParameter::Convention>();
    if (convention != m_convention)
    {
        m_convention = convention;
        emit conventionChanged(convention);
    }
}

void EulerFrameParameterWidget::onSliderValueChanged(int index, int value)
{
    if (!m_isSliderUpdating)
    {
        m_angleSpin[index]->setValue(value);
    }
}

void EulerFrameParameterWidget::onSpinBoxValueChanged(int index, double value)
{
    double& currentValue = index == 0 ? m_a : (index == 1 ? m_b : m_c);
    if (currentValue != value)
    {
        m_isSliderUpdating = true;
        currentValue = value;
        m_angleSlider[index]->setValue(static_cast<int>(value));
        m_isSliderUpdating = false;

        if (index == 0)
            emit aChanged(m_a);
        else if (index == 1)
            emit bChanged(m_b);
        else
            emit cChanged(m_c);
    }
}
