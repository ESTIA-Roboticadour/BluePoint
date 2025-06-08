#include "StringParameterWidget.h"

#include <QHBoxLayout>
#include <QFileDialog>

StringParameterWidget::StringParameterWidget(bool readOnly, QWidget* parent) :
    ParameterWidget(parent),
	m_name("String Parameter"),
	m_label(new QLabel("String Parameter:", this)),
    m_lineEdit(new QLineEdit(this)),
    m_browseBtn(nullptr),
    m_kind(StringParameter::Kind::Plain),
    m_canEditPath(true),
    m_readOnly(readOnly)
{
    m_lineEdit->setPlaceholderText("Value");

    QHBoxLayout* layoutControls = new QHBoxLayout(this);
	layoutControls->addWidget(m_label);
	layoutControls->addWidget(m_lineEdit);

    if (m_readOnly)
    {
        m_lineEdit->setEnabled(false);
    }
    else
    {
        m_browseBtn = new QPushButton("…", this);
        m_browseBtn->setFixedWidth(24);
        layoutControls->addWidget(m_browseBtn);

        connect(m_lineEdit, &QLineEdit::editingFinished, this, &StringParameterWidget::onEditingFinished);
        connect(m_browseBtn, &QPushButton::clicked, this, &StringParameterWidget::onBrowseClicked);
        updateBrowseVisibility();
    }
}

QString StringParameterWidget::getName() const { return m_name; }

void StringParameterWidget::setName(const QString& newName)
{
	if (m_name != newName)
	{
		m_name = newName;
		m_label->setText(m_name + ':');
		emit nameChanged(newName);
	}
}

QString StringParameterWidget::getValue() const { return m_lineEdit->text(); }

void StringParameterWidget::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if (m_readOnly)
    {
        m_lineEdit->setEnabled(false);
    }
}

void StringParameterWidget::setFrom(const StringParameter* parameter)
{
	setName(parameter->getName());
	setValue(parameter->getValue());
    setKind(parameter->getKind());
    setCanEditPath(parameter->getCanEditPath());
	setEnabled(parameter->getIsEditable());

    if (!parameter->getCanEditPath())
    {
        connect(m_lineEdit, &QLineEdit::textChanged, this, &StringParameterWidget::valueChanged);
    }
}

void StringParameterWidget::setValue(const QString& val) { m_lineEdit->setText(val); }

StringParameter::Kind StringParameterWidget::getKind() const { return m_kind; }

bool StringParameterWidget::canEditPath() const { return m_canEditPath; }

int StringParameterWidget::getLabelWidth() const
{
    return m_label->sizeHint().width();
}

void StringParameterWidget::setLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

void StringParameterWidget::setKind(StringParameter::Kind k)
{
    if (m_kind != k) {
        m_kind = k;
        updateBrowseVisibility();
        emit kindChanged(m_kind);
    }
}

void StringParameterWidget::setCanEditPath(bool canEditPath)
{
    if (m_canEditPath != canEditPath)
    {
        m_canEditPath = canEditPath;
        m_lineEdit->setEnabled(m_canEditPath && isEnabled());
        emit canEditPathChanged(m_canEditPath);
    }
}

void StringParameterWidget::updateBrowseVisibility()
{
    if (m_browseBtn)
        m_browseBtn->setVisible(m_kind != StringParameter::Kind::Plain);
}

void StringParameterWidget::onEditingFinished()
{
	emit valueChanged(m_lineEdit->text());
}

void StringParameterWidget::onBrowseClicked()
{
    QString path;
    switch (m_kind) {
    case StringParameter::Kind::FilePath:
        path = QFileDialog::getOpenFileName(this, tr("Select file"), getValue());
        break;
    case StringParameter::Kind::DirectoryPath:
        path = QFileDialog::getExistingDirectory(this, tr("Select folder"), getValue());
        break;
    default:
        return;
    }
    if (!path.isEmpty())
        setValue(path);          // met à jour l'IHM et émet valueChanged()
}
