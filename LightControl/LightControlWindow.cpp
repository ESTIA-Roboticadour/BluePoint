#include "LightControlWindow.h"
#include <QLineEdit>

LightControlWindow::LightControlWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::LightControlWindowClass()),
    m_relayButtons(),
	m_ledIndicators()
{
    m_ui->setupUi(this);

	m_ui->comboBox->lineEdit()->setReadOnly(true);
    m_ui->comboBox->lineEdit()->setPlaceholderText("Select COM port");

    m_relayButtons.append(m_ui->relay1PushButton);
    m_relayButtons.append(m_ui->relay2PushButton);
    m_relayButtons.append(m_ui->relay3PushButton);
    m_relayButtons.append(m_ui->relay4PushButton);

    m_ledIndicators.append(m_ui->led1Label);
    m_ledIndicators.append(m_ui->led2Label);
    m_ledIndicators.append(m_ui->led3Label);
    m_ledIndicators.append(m_ui->led4Label);

    clearModuleInfo();
    setButtonsEnabled(false);

    connect(m_ui->comboBox, &QComboBox::currentIndexChanged, this, &LightControlWindow::onPortSelectedChanged);
	for (int i = 0; i < m_relayButtons.size(); ++i) {
		connect(m_relayButtons[i], &QPushButton::clicked, this, [this, i]() { emit relayButtonPressed(i); });
	}
}

LightControlWindow::~LightControlWindow()
{
    delete m_ui;
}

void LightControlWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    emit closeRequest();
}

void LightControlWindow::onPortSelectedChanged(int index)
{
	emit portSelectedChanged(index < 0 || index >= m_ui->comboBox->count() ? "" : m_ui->comboBox->itemText(index));
}

void LightControlWindow::setAvailablePorts(const QStringList& ports)
{
    m_ui->comboBox->clear();
	if (ports.isEmpty()) 
    {
        m_ui->comboBox->lineEdit()->setPlaceholderText("No available ports");
	}
    else
    {
        m_ui->comboBox->addItems(ports);
    }
}

void LightControlWindow::setButtonsEnabled(bool enabled)
{
	for (QPushButton* button : m_relayButtons) {
		button->setEnabled(enabled);
	}
}

void LightControlWindow::clearModuleInfo() const
{
	m_ui->idLabel->clear();
	m_ui->versionLabel->clear();
}

void LightControlWindow::setModuleInfo(int id, int version)
{
    m_ui->idLabel->setText(QString::number(id));
    m_ui->versionLabel->setText(QString::number(version));
}

void LightControlWindow::setRelayState(int relayIndex, bool on)
{
    if (relayIndex < 0 || relayIndex >= m_ledIndicators.size()) 
        return;
    m_ledIndicators[relayIndex]->setStyleSheet(QString("background-color: %1; border-radius: 5px;").arg(on ? "green" : "gray"));
}

void LightControlWindow::setSelectedPort(int index)
{
    int i = index < 0 || index >= m_ui->comboBox->count() ? -1 : index;
	setButtonsEnabled(i >= 0);
    m_ui->comboBox->setCurrentIndex(i);
}
