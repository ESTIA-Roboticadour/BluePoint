#include "ConfigurationView.h"
#include "Helper.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QSizePolicy>
#include <QFileInfo>
#include <QFont>
#include <QPalette>
#include <QColor>
#include <QFileDialog>
#include <QGroupBox>
#include <QSpacerItem>

ConfigurationView::ConfigurationView(const QString& title, bool isReadOnly, QWidget* parent) :
	TransparentScrollArea(parent),
	m_configPath(),
	m_isConfigModified(false),
	m_isFullPath(false)
{
	buildUi(title, isReadOnly);
}

void ConfigurationView::buildUi(const QString& titleStr, bool isReadOnly)
{
	/* ---- widget qui contiendra tout le contenu défilable ---- */
	auto* content = new QWidget(scrollArea());
	scrollArea()->setWidget(content);

	/* ---- layout principal DU CONTENU ---- */
	auto* vMain = new QVBoxLayout(content);        // parent = content, pas this
	vMain->setContentsMargins(16, 16, 16, 16);
	vMain->setSpacing(8);

	/* ---- titre ---- */
	auto* title = new QLabel(titleStr, content);
	QFont f = title->font();
	f.setPointSizeF(f.pointSizeF() * 1.6);
	f.setBold(true);
	title->setFont(f);
	vMain->addWidget(title);

	/* ---- séparateur ---- */
	auto* sep = new QFrame(content);
	sep->setFrameShape(QFrame::HLine);
	sep->setFrameShadow(QFrame::Sunken);
	vMain->addWidget(sep);

	/* ---- file ---- */
	auto* fileLayout = new QHBoxLayout();
	auto* fileLabel = new QLabel("File:", content);
	m_fullPathButton = new QPushButton("▸", content); // ◂
	m_pathLabel = new QLabel(content);
	fileLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
	m_fullPathButton->setFixedWidth(24);
	m_fullPathButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
	fileLayout->addWidget(fileLabel);
	fileLayout->addWidget(m_fullPathButton);
	fileLayout->addWidget(m_pathLabel);
	vMain->addLayout(fileLayout);

	/* ---- séparateur 2 ---- */
	sep = new QFrame(content);
	sep->setFrameShape(QFrame::HLine);
	sep->setFrameShadow(QFrame::Sunken);
	vMain->addWidget(sep);

	/* ---- vue des paramètres ---- */
	QGroupBox* box = new QGroupBox("Parameters", content);
	box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	auto* boxLayout = new QVBoxLayout(box);

	m_parametersView = new ParametersView(box);
	m_parametersView->setReadOnly(isReadOnly);
	m_parametersView->setAlignment(ParametersView::Alignment::NoAlignment);
	m_parametersView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	boxLayout->addWidget(m_parametersView);

	vMain->addWidget(box);

	vMain->addSpacerItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

	/* ---- boutons ---- */
	auto* hBtns = new QHBoxLayout();
	hBtns->setAlignment(Qt::AlignRight);
	m_cancelButton = new QPushButton(tr("Cancel"), content);
	m_resetButton = new QPushButton(tr("Reset"), content);
	m_openButton = new QPushButton(tr("Open"), content);
	m_saveButton = new QPushButton(tr("Save"), content);

	m_cancelButton->setEnabled(false);
	m_resetButton->setEnabled(false);
	m_openButton->setEnabled(false);
	m_saveButton->setEnabled(false);

	hBtns->addStretch();
	hBtns->addWidget(m_cancelButton);
	hBtns->addWidget(m_resetButton);
	hBtns->addWidget(m_openButton);
	hBtns->addWidget(m_saveButton);

	vMain->addLayout(hBtns);

	/* ---- connexions ---- */
	connect(m_fullPathButton, &QPushButton::clicked, this, &ConfigurationView::onFullPathButtonClicked);
	connect(m_cancelButton, &QPushButton::clicked, this, &ConfigurationView::cancelRequested);
	connect(m_resetButton, &QPushButton::clicked, this, &ConfigurationView::resetRequested);
	connect(m_openButton, &QPushButton::clicked, this, &ConfigurationView::onOpenButtonClicked);
	connect(m_saveButton, &QPushButton::clicked, this, &ConfigurationView::onSaveButtonClicked);
}

void ConfigurationView::updateUiConfig(bool isModified)
{
	if (m_isConfigModified != isModified)
	{
		m_isConfigModified = isModified;
		updateFileLabel();

		QFont f = m_pathLabel->font();   // on récupère la police courante
		if (m_isConfigModified)
		{
			f.setItalic(true);				 // on active l’italique
			m_cancelButton->setEnabled(true);
			m_saveButton->setEnabled(true);
		}
		else
		{
			f.setItalic(false);				 // on désactive l’italique
			m_cancelButton->setEnabled(false);
			m_saveButton->setEnabled(false);
		}
		m_pathLabel->setFont(f);         // on ré-applique la police modifiée
	}
}

void ConfigurationView::updateFileLabel()
{
	m_pathLabel->setText(m_configPath.isEmpty() ? "Not saved" : ((m_isFullPath ? m_configPath : QFileInfo(m_configPath).fileName()) + (m_isConfigModified ? "*" : "")));
	m_pathLabel->setToolTip(m_configPath);
}

void ConfigurationView::setConfig(const Config* config)
{
	if (config)
	{
		m_configPath = config->getPath();
		m_isConfigModified = true; // set to true to be sure next updateUiConfig(false) will be applied
		updateUiConfig(false);
		QList<ParameterBase*> params = config->getParameters();
		QList<const ParameterBase*> constParams;
		for (auto* param : params)
		{
			constParams.append(param);
		}
		m_parametersView->setParameters(constParams);

		m_resetButton->setEnabled(true);
		m_openButton->setEnabled(true);
		m_saveButton->setEnabled(true);
	}
	else
	{
		m_isConfigModified = false;

		m_configPath.clear();
		m_pathLabel->clear();
		m_pathLabel->setToolTip("");
		m_parametersView->setParameters(QList<const ParameterBase*>());

		m_cancelButton->setEnabled(false);
		m_resetButton->setEnabled(false);
		m_openButton->setEnabled(false);
		m_saveButton->setEnabled(false);
	}
}

void ConfigurationView::onFullPathButtonClicked()
{
	m_isFullPath = !m_isFullPath;
	m_fullPathButton->setText(m_isFullPath ? "◂" : "▸");
	updateFileLabel();
}

void ConfigurationView::onSaveButtonClicked()
{
	QString dir;
	QString fileName;
	if (!m_configPath.isEmpty())
	{
		const QFileInfo fi(m_configPath);
		dir = fi.dir().path();
		fileName = fi.fileName();
	}

	QString path = Helper::getSaveConfigFile(this, fileName, dir);
	if (!path.isEmpty())
	{
		emit saveRequested(path);
	}
}

void ConfigurationView::onOpenButtonClicked()
{
	QString dir = m_configPath.isEmpty() ? "" : QFileInfo(m_configPath).dir().path();
	const QString path = Helper::getOpenConfigFile(this, dir);
	if (!path.isEmpty())
	{
		emit openRequested(path);
	}
}

void ConfigurationView::onConfigModified()
{
	updateUiConfig(true);
}

void ConfigurationView::onConfigCanceled()
{
	updateUiConfig(false);
}

void ConfigurationView::onConfigSaved(const Config* config)
{
	m_configPath = config->getPath();
	m_isConfigModified = true; // to force UI to refresh
	updateUiConfig(false);
}
