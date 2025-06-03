#include "DeviceView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QScrollArea>
#include <QSizePolicy>

DeviceView::DeviceView(QWidget* parent) :
    QWidget(parent)
{
    buildUi();
}

void DeviceView::buildUi()
{
    // ---- outer layout with coloured margins ----
    auto* outer = new QHBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);

    // scroll area (shows red scroll bar when needed)
    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    outer->addWidget(scrollArea, 1);

    // ---- content inside scroll area ----
    auto* content = new QWidget(scrollArea);
    scrollArea->setWidget(content);

    auto* vMain = new QVBoxLayout(content);
    vMain->setContentsMargins(16, 16, 16, 16);
    vMain->setSpacing(8);

    // title
    auto* title = new QLabel(tr("Device"), content);
    QFont f = title->font();
    f.setPointSizeF(f.pointSizeF() * 1.6);
    f.setBold(true);
    title->setFont(f);
    vMain->addWidget(title);

    // separator
    auto* sep = new QFrame(content);
    sep->setFrameShape(QFrame::HLine);
    sep->setFrameShadow(QFrame::Sunken);
    vMain->addWidget(sep);

    // ---- main horizontal zone ----
    auto* hMain = new QHBoxLayout();
    hMain->setSpacing(8);
    vMain->addLayout(hMain, 1);

    // frame viewer (left, takes most space)
    m_frameViewer = new FrameViewer(content);
    m_frameViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hMain->addWidget(m_frameViewer, 3);

    // right column
    auto* vRight = new QVBoxLayout();
    vRight->setSpacing(8);
    hMain->addLayout(vRight);

    // ---- Light group ----
    auto* lightBox = new QGroupBox(tr("Light"), content);
    vRight->addWidget(lightBox);
    auto* vLight = new QVBoxLayout(lightBox);

    auto* form = new QFormLayout();
    m_comLabel = new QLabel("", lightBox);
    m_relayLabel = new QLabel("", lightBox);
    form->addRow(tr("COM:"), m_comLabel);
    form->addRow(tr("Relay:"), m_relayLabel);
    vLight->addLayout(form);

    auto* hBtns = new QHBoxLayout();
    m_onButton = new QPushButton(tr("On"), lightBox);
    m_offButton = new QPushButton(tr("Off"), lightBox);
    hBtns->addWidget(m_onButton);
    hBtns->addWidget(m_offButton);
    vLight->addLayout(hBtns);

    connect(m_onButton, &QPushButton::clicked, this, &DeviceView::lightOnRequested);
    connect(m_offButton, &QPushButton::clicked, this, &DeviceView::lightOffRequested);

    // ---- Camera group ----
    auto* camBox = new QGroupBox(tr("Camera"), content);
    vRight->addWidget(camBox, 1);
    auto* vCam = new QVBoxLayout(camBox);

    m_parametersView = new ParametersView(camBox);
    m_parametersView->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

    vCam->addWidget(m_parametersView);

    vRight->addStretch();   // push items to top
    vMain->addStretch();    // allow scrolling if needed
}

void DeviceView::setLightInfo(const QString& comPort, int relay)
{
    m_comLabel->setText(comPort);
    m_relayLabel->setText(QString::number(relay));
}

void DeviceView::setButtonsState(bool enabled)
{
	m_onButton->setEnabled(enabled);
	m_offButton->setEnabled(enabled);
}

void DeviceView::setCameraConfig(const CameraConfig* cameraConfig)
{
    if (cameraConfig)
    {
        QList<ParameterBase*> params = cameraConfig->getParameters();
		QList<const ParameterBase*> constParams;
		for (auto* param : params)
		{
			constParams.append(param);
		}
		m_parametersView->setParameters(constParams);
    }
    else
    {
        m_parametersView->setParameters(QList<const ParameterBase*>());
    }
}
