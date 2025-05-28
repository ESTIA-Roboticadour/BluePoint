#include "ConfigurationView.h"
#include "Helper.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QScrollArea>
#include <QSizePolicy>
#include <QFileDialog>
#include <QFileInfo>

ConfigurationView::ConfigurationView(const QString& title, QWidget* parent) :
	QWidget(parent),
	m_configPath()
{
	buildUi(title);
}

void ConfigurationView::buildUi(const QString& titleStr)
{
    /* ---- outer layout (entoure toute la vue) ---- */
    auto* outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);

    /* ---- scroll area (affiche la barre de défilement si nécessaire) ---- */
    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    outer->addWidget(scrollArea);

    /* ---- widget qui contiendra tout le contenu défilable ---- */
    auto* content = new QWidget(scrollArea);       // ! contenu de la scroll-area
    scrollArea->setWidget(content);

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

    /* ---- vue des paramètres ---- */
    m_parametersView = new ParametersView(content);
    m_parametersView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    vMain->addWidget(m_parametersView);

    /* ---- boutons ---- */
    auto* hBtns = new QHBoxLayout();
    m_cancelButton = new QPushButton(tr("Cancel"), content);
    m_resetButton = new QPushButton(tr("Reset"), content);
    m_saveButton = new QPushButton(tr("Save"), content);
    hBtns->addWidget(m_cancelButton);
    hBtns->addWidget(m_resetButton);
    hBtns->addWidget(m_saveButton);
    vMain->addLayout(hBtns);

    /* ---- connexions ---- */
    connect(m_cancelButton, &QPushButton::clicked, this, &ConfigurationView::cancelRequested);
    connect(m_resetButton, &QPushButton::clicked, this, &ConfigurationView::resetRequested);
    connect(m_saveButton, &QPushButton::clicked, this, &ConfigurationView::onSaveButtonClicked);
}

void ConfigurationView::onSaveButtonClicked()
{
	const QFileInfo fi(m_configPath);
	const QString dir = fi.dir().path();
	const QString fileName = fi.fileName();

	QString path = Helper::getSaveConfigFile(this, fileName, dir);
	if (!path.isEmpty())
	{
		emit saveRequested(path);
	}
}

void ConfigurationView::setConfig(const Config* config)
{
	if (config)
	{
		m_configPath = config->getPath();
		QList<ParameterBase*> params = config->getParameters();
		QList<const ParameterBase*> constParams;
		for (auto* param : params)
		{
			constParams.append(param);
		}
		m_parametersView->setParameters(constParams);
	}
	else
	{
		m_configPath.clear();
		m_parametersView->setParameters(QList<const ParameterBase*>());
	}
}
