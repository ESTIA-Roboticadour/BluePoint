#include "Matrix4x4ParameterWidget.h"

#include <QDoubleValidator>

Matrix4x4ParameterWidget::Matrix4x4ParameterWidget(QWidget* parent) :
    ParameterWidget(parent),
    m_name("Matrix 4x4"),
    m_label(new QLabel("Matrix 4x4:", this)),
    m_layout(new QGridLayout(this))
{
    setupUI();
}

void Matrix4x4ParameterWidget::setupUI()
{
    m_layout->addWidget(m_label, 0, 0, 1, 4); // Label spanning 4 columns

    QDoubleValidator* validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            QLineEdit* edit = new QLineEdit("0.00", this);
            edit->setValidator(validator);
            //edit->setMaximumWidth(60);
            m_layout->addWidget(edit, row + 1, col);
            m_lineEdits.append(edit);

            connect(edit, &QLineEdit::editingFinished, this, &Matrix4x4ParameterWidget::onLineEditEdited);
        }
    }

    setLayout(m_layout);
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

QMatrix4x4 Matrix4x4ParameterWidget::getMatrix() const
{
    return m_matrix;
}

void Matrix4x4ParameterWidget::setMatrix(const QMatrix4x4& matrix)
{
    if (m_matrix != matrix)
    {
        m_matrix = matrix;
        updateUIFromMatrix(m_matrix);
        emit matrixChanged(m_matrix);
    }
}

void Matrix4x4ParameterWidget::setRotationMatrix(const QMatrix4x4& rotation)
{
    QMatrix4x4 current = getMatrix();

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            current(row, col) = rotation(row, col);

    setMatrix(current);
}

void Matrix4x4ParameterWidget::setTranslation(const QVector3D& translation)
{
    QMatrix4x4 current = getMatrix();

    current(0, 3) = translation.x();
    current(1, 3) = translation.y();
    current(2, 3) = translation.z();

    setMatrix(current);
}

void Matrix4x4ParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

int Matrix4x4ParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void Matrix4x4ParameterWidget::updateUIFromMatrix(const QMatrix4x4& matrix)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            int index = row * 4 + col;
            m_lineEdits[index]->setText(QString::number(matrix(row, col), 'f', 3));
        }
    }
}

void Matrix4x4ParameterWidget::setFrom(const Matrix4x4Parameter* matrix4x4Parameter)
{
    if (!matrix4x4Parameter)
        return;

    setName(matrix4x4Parameter->getName());
    setMatrix(matrix4x4Parameter->getMatrix());
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

    setMatrix(newMatrix);
}

