#include "Matrix4x4ParameterWidget.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QSizePolicy>

Matrix4x4ParameterWidget::Matrix4x4ParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
    m_name("Matrix 4x4"),
    m_matrix(),
    m_readOnly(readOnly),
    m_label(new QLabel("Matrix 4x4:", this)),
    m_layout(new QHBoxLayout(this)),
    m_button(nullptr)
{
    setupUI();
    updateUIFromMatrix();
}

void Matrix4x4ParameterWidget::setupUI()
{
    m_layout->addWidget(m_label);
    m_label->setAlignment(Qt::AlignTop);

    QVBoxLayout* vBox = new QVBoxLayout();
    QGridLayout* gridLayout = new QGridLayout();

    QDoubleValidator* validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            QLineEdit* edit = new QLineEdit(this);
            edit->setValidator(validator);
            gridLayout->addWidget(edit, row + 1, col);
            m_lineEdits.append(edit);

            if (m_readOnly)
            {
                edit->setEnabled(false);
            }
            else
            {
                connect(edit, &QLineEdit::editingFinished, this, &Matrix4x4ParameterWidget::onLineEditEdited);
            }
        }
    }

    vBox->addLayout(gridLayout);

    for (int col = 0; col < 3; ++col)
    {
        int index = 3 * 4 + col;
        m_lineEdits[index]->setEnabled(false);
    }

    if (!m_readOnly)
    {
        m_button = new QPushButton("Normalize", this);
        m_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        vBox->addWidget(m_button);
        connect(m_button, &QPushButton::clicked, this, &Matrix4x4ParameterWidget::onButtonClicked);
    }
    m_layout->addLayout(vBox);
}

QString Matrix4x4ParameterWidget::getName() const
{
    return m_name;
}

void Matrix4x4ParameterWidget::setName(const QString& newName)
{
    if (m_name != newName)
    {
        m_name = newName;
        m_label->setText(newName + ':');
        emit nameChanged(newName);
    }
}

QMatrix4x4 Matrix4x4ParameterWidget::getValue() const
{
    return m_matrix;
}

void Matrix4x4ParameterWidget::setValue(const QMatrix4x4& matrix)
{
    if (m_matrix != matrix)
    {
        m_matrix = matrix;
        updateUIFromMatrix();
        emit matrixChanged(m_matrix);
    }
}

void Matrix4x4ParameterWidget::setRotationMatrix(const QMatrix4x4& rotation)
{
    QMatrix4x4 current = getValue();

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            current(row, col) = rotation(row, col);

    setValue(current);
}

void Matrix4x4ParameterWidget::setTranslation(const QVector3D& translation)
{
    QMatrix4x4 current = getValue();

    current(0, 3) = translation.x();
    current(1, 3) = translation.y();
    current(2, 3) = translation.z();

    setValue(current);
}

void Matrix4x4ParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

int Matrix4x4ParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void Matrix4x4ParameterWidget::updateUIFromMatrix()
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            int index = row * 4 + col;
            m_lineEdits[index]->setText(QString::number(m_matrix(row, col), 'f', 3));
        }
    }
}

void Matrix4x4ParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly)
    {
        for (auto& edit : m_lineEdits)
            edit->setEnabled(false);
    }
    else
    {
        for (int col = 0; col < 3; ++col)
        {
            int index = 3 * 4 + col;
            m_lineEdits[index]->setEnabled(false);
        }
    }
}

void Matrix4x4ParameterWidget::setFrom(const Matrix4x4Parameter* matrix4x4Parameter)
{
    if (!matrix4x4Parameter)
        return;

    setName(matrix4x4Parameter->getName());
    setValue(matrix4x4Parameter->getValue());
    setEnabled(matrix4x4Parameter->getIsEditable());
    updateUIFromMatrix();
}

void Matrix4x4ParameterWidget::onLineEditEdited()
{
    QMatrix4x4 newMatrix;

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            int index = row * 4 + col;
            bool ok = false;
            float value = m_lineEdits[index]->text().toFloat(&ok);
            if (!ok)
                return;

            newMatrix(row, col) = value;
        }
    }
    setValue(newMatrix);
}

void Matrix4x4ParameterWidget::onButtonClicked()
{
    QMatrix4x4 newMatrix = m_matrix;
    for (int i = 0; i < 3; ++i) {
        QVector3D col = newMatrix.column(i).toVector3D().normalized();
        newMatrix.setColumn(i, QVector4D(col, 0.0f));
    }
    setValue(newMatrix);
}
