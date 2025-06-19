#include "AppView.h"
#include "TransparentScrollArea.h"
#include "Helper.h"

#include <QHBoxLayout>
#include <QComboBox>
#include <QSizePolicy>
#include <QStringList>
#include <QList>
#include <QLocale>

AppView::AppView(QWidget* parent) :
	TransparentScrollArea(parent),
	m_poseLineEdits(6),
	m_deltaLineEdits(6),
	m_axisButtons(12),
	m_jointButtons(12),
	m_poseLabels(6),
	m_deltaLabels(6),
	m_ioButtons(32),
	m_uiTimer(),
	m_freshRateHz(20),
	m_isReadyToMove(false),
	m_isJoggingCartesian(true),
	m_isAzerty(true)
{
	setupUI();
	m_uiTimer.setInterval(static_cast<int>(1000.0 / m_freshRateHz));
	m_uiTimer.setTimerType(Qt::PreciseTimer);
	connect(&m_uiTimer, &QTimer::timeout, this, &AppView::refreshUI, Qt::DirectConnection);
}

void AppView::setupUI()
{
	/* ---- widget qui contiendra tout le contenu défilable ---- */
	auto* content = new QWidget(scrollArea());
	scrollArea()->setWidget(content);

	auto* mainLayout = new QHBoxLayout();

	// Gauche : colonne

	auto* leftLayout = new QVBoxLayout();

	// 1ère ligne : ParametersView
	m_parametersView = new ParametersView();
	//m_parametersView->setReadOnly(true);
	m_parametersView->setAlignment(ParametersView::Alignment::All);
	m_parametersView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	leftLayout->addWidget(m_parametersView);

	leftLayout->addStretch();

	// Droite : colonne
	auto* rightLayout = new QVBoxLayout();

	// Group Status
	auto* statusGroup = new QGroupBox("Status", this);
	statusGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	auto* groupLayout = new QVBoxLayout();
	auto* statusLayout = new QHBoxLayout();
	auto* behaviourLayout = new QHBoxLayout();
	m_statusLabel = new QLabel("", statusGroup);
	m_robotStateLabel = new QLabel("", statusGroup);

	statusLayout->addWidget(new QLabel("Status:", statusGroup));
	statusLayout->addWidget(m_statusLabel);
	statusLayout->addStretch();
	behaviourLayout->addWidget(new QLabel("Robot behaviour:", statusGroup));
	behaviourLayout->addWidget(m_robotStateLabel);
	behaviourLayout->addStretch();

	groupLayout->addLayout(statusLayout);
	groupLayout->addLayout(behaviourLayout);

	statusGroup->setLayout(groupLayout);
	rightLayout->addWidget(statusGroup);

	// Groupe Connection
	auto* connectionGroup = new QGroupBox("Connection", this);
	connectionGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	m_connectionLayout = new QVBoxLayout();
	auto* connectionBtnsLayout = new QHBoxLayout();
	m_connectButton = new QPushButton("Connect", this);
	m_disconnectButton = new QPushButton("Disconnect", this);
	m_connectButton->setEnabled(false);
	m_disconnectButton->setEnabled(false);
	connectionBtnsLayout->addWidget(m_connectButton);
	connectionBtnsLayout->addWidget(m_disconnectButton);
	connectionBtnsLayout->addStretch();

	m_connectionLayout->addLayout(connectionBtnsLayout);

	connectionGroup->setLayout(m_connectionLayout);
	rightLayout->addWidget(connectionGroup);

	// Groupe "Control"
	auto* controlGroup = new QGroupBox("Control", this);
	controlGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	auto* controlLayout = new QVBoxLayout();

	// Ligne 1 : Start / Stop
	auto* jobGroup = new QGroupBox("Job", this);

	auto* startStopLayout = new QHBoxLayout();
	jobGroup->setLayout(startStopLayout);

	m_startButton = new QPushButton("Start", this);
	m_stopButton = new QPushButton("Stop", this);
	m_startButton->setEnabled(false);
	m_stopButton->setEnabled(false);
	startStopLayout->addWidget(m_startButton);
	startStopLayout->addWidget(m_stopButton);
	startStopLayout->addStretch();

	controlLayout->addWidget(jobGroup);

	// Ligne 2 : Move & IO
	auto* moveIoContent = new QWidget();
	moveIoContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	auto* moveIoLayout = new QHBoxLayout(moveIoContent);
	moveIoLayout->setContentsMargins(0, 0, 0, 0);

	auto* moveGroup = new QGroupBox("Move", this);
	moveGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	moveIoLayout->addWidget(moveGroup);

	auto* moveLayout = new QVBoxLayout(moveGroup);

	// ComboBox base
	auto* baseLayout = new QHBoxLayout();
	auto* baseLabel = new QLabel("Base:");
	baseLayout->addWidget(baseLabel);
	QComboBox* baseComboBox = new QComboBox();
	baseComboBox->setFixedWidth(80);
	baseComboBox->addItems({ "BASE", "TOOL" });
	baseComboBox->setCurrentIndex(0);
	baseComboBox->setDisabled(true);
	connect(baseComboBox, &QComboBox::currentIndexChanged, this, &AppView::onBaseComboBoxChanged);

	baseLayout->addWidget(baseComboBox);
	moveLayout->addLayout(baseLayout);
	baseLayout->addStretch();

	// Onglets cartésien/articulaire
	auto* modeTabs = new QTabWidget(this);
	modeTabs->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
	auto* cartesianWidget = new QWidget();
	auto* articularWidget = new QWidget();
	modeTabs->setAttribute(Qt::WA_TranslucentBackground);
	cartesianWidget->setAttribute(Qt::WA_TranslucentBackground);
	articularWidget->setAttribute(Qt::WA_TranslucentBackground);

	modeTabs->addTab(cartesianWidget, "Cartesian");
	modeTabs->addTab(articularWidget, "Articular");
	moveLayout->addWidget(modeTabs);

	connect(modeTabs, &QTabWidget::currentChanged, this, &AppView::onMoveTabChanged);

	// Layout cartésien : boutons de déplacement
	auto* cartesianLayout = new QGridLayout(cartesianWidget);
	cartesianLayout->setSpacing(0);
	cartesianLayout->setContentsMargins(0, 2, 0, 2);

	createMovementButtons(cartesianLayout);

	// Layout articulaire : boutons J1-J6
	auto* articularLayout = new QGridLayout(articularWidget);
	articularLayout->setSpacing(0);
	articularLayout->setContentsMargins(0, 2, 0, 2);
	createJointControlButtons(articularLayout);

	// IO Group
	QGroupBox* ioGroup = new QGroupBox("I/O", this);
	ioGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	auto* gridLayout = new QGridLayout(ioGroup);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(2, 4, 2, 4);
	createIOBtns(gridLayout);

	moveIoLayout->addWidget(ioGroup);
	controlLayout->addWidget(moveIoContent);

	// Ligne 3 : Position + Delta
	auto* posDeltaLayout = new QHBoxLayout();

	auto* positionGroup = createPoseGroup("Position", m_poseLabels, m_poseLineEdits);
	auto* deltaGroup = createPoseGroup("Delta", m_deltaLabels, m_deltaLineEdits);
	m_isJoggingCartesian = !m_isJoggingCartesian;	// Petite astuce Sioux pour actualis
	setIsJoggingInCartesian(!m_isJoggingCartesian); //

	posDeltaLayout->addWidget(positionGroup);
	posDeltaLayout->addWidget(deltaGroup);

	controlLayout->addLayout(posDeltaLayout);

	controlGroup->setLayout(controlLayout);
	rightLayout->addWidget(controlGroup);
	rightLayout->addStretch();

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);

	// Connexions
	connect(m_connectButton, &QPushButton::clicked, this, &AppView::onConnectButtonClicked);
	connect(m_disconnectButton, &QPushButton::clicked, this, &AppView::onDisconnectButtonClicked);
	connect(m_startButton, &QPushButton::clicked, this, &AppView::onStartButtonClicked);
	connect(m_stopButton, &QPushButton::clicked, this, &AppView::onStopButtonClicked);

	content->setLayout(mainLayout);
}

void AppView::createMovementButtons(QGridLayout* layout)
{
	static const char axisLabels[6] = { 'X', 'Y', 'Z', 'A', 'B', 'C' };
	for (int i = 0; i < 6; ++i)
	{
		QLabel* axisLabel = new QLabel(QString("%1").arg(axisLabels[i]), this);
		axisLabel->setMinimumWidth(15);
		axisLabel->setAlignment(Qt::AlignCenter);
		axisLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

		QPushButton* plusButton = new QPushButton("+", this);
		QPushButton* minusButton = new QPushButton("-", this);
		plusButton->setFixedSize(30, 30);
		minusButton->setFixedSize(30, 30);
		plusButton->setEnabled(false);
		minusButton->setEnabled(false);

		QHBoxLayout* btnLayout = new QHBoxLayout();
		btnLayout->setContentsMargins(3, 0, 3, 0);
		btnLayout->setSpacing(1);
		btnLayout->addWidget(axisLabel);
		btnLayout->addWidget(plusButton);
		btnLayout->addWidget(minusButton);

		QWidget* group = new QWidget(this);
		group->setLayout(btnLayout);

		int row = i % 3;
		int col = (i < 3) ? 0 : 2; // 0 pour X à Z, 2 pour A à C

		layout->addWidget(group, row, col);

		connect(plusButton, &QPushButton::pressed, this, [this, i]() { emit cartesianMovementPressed(static_cast<RobotKuka::Axis>(i), true); });
		connect(plusButton, &QPushButton::released, this, [this, i]() { emit cartesianMovementReleased(static_cast<RobotKuka::Axis>(i)); });
		connect(minusButton, &QPushButton::pressed, this, [this, i]() { emit cartesianMovementPressed(static_cast<RobotKuka::Axis>(i), false); });
		connect(minusButton, &QPushButton::released, this, [this, i]() { emit cartesianMovementReleased(static_cast<RobotKuka::Axis>(i)); });
		m_axisButtons[2 * i] = plusButton;
		m_axisButtons[2 * i + 1] = minusButton;
	}

	// Ligne verticale entre les deux groupes
	QFrame* line = new QFrame(this);
	line->setFrameShape(QFrame::VLine);
	line->setFrameShadow(QFrame::Sunken);
	layout->addWidget(line, 0, 1, 3, 1); // ligne verticale sur 3 lignes
}

void AppView::createJointControlButtons(QGridLayout* layout)
{
	for (int i = 0; i < 6; ++i)
	{
		QString label = QString("J%1").arg(i + 1);
		QLabel* jointLabel = new QLabel(label, this);
		jointLabel->setMinimumWidth(15);
		jointLabel->setAlignment(Qt::AlignCenter);
		jointLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

		QPushButton* plusButton = new QPushButton("+", this);
		QPushButton* minusButton = new QPushButton("-", this);
		plusButton->setFixedSize(30, 30);
		minusButton->setFixedSize(30, 30);
		plusButton->setEnabled(false);
		minusButton->setEnabled(false);

		QHBoxLayout* btnLayout = new QHBoxLayout();
		btnLayout->setContentsMargins(3, 0, 3, 0);
		btnLayout->setSpacing(1);
		btnLayout->addWidget(jointLabel);
		btnLayout->addWidget(plusButton);
		btnLayout->addWidget(minusButton);

		QWidget* group = new QWidget(this);
		group->setLayout(btnLayout);

		int row = i % 3;
		int col = (i < 3) ? 0 : 2; // 0 pour J1 à J3, 2 pour J4 à J6

		layout->addWidget(group, row, col);

		connect(plusButton, &QPushButton::pressed, this, [this, i]() { emit articularMovementPressed(static_cast<RobotKuka::Joint>(i), true); });
		connect(plusButton, &QPushButton::released, this, [this, i]() { emit articularMovementReleased(static_cast<RobotKuka::Joint>(i)); });
		connect(minusButton, &QPushButton::pressed, this, [this, i]() { emit articularMovementPressed(static_cast<RobotKuka::Joint>(i), false); });
		connect(minusButton, &QPushButton::released, this, [this, i]() { emit articularMovementReleased(static_cast<RobotKuka::Joint>(i)); });
		m_jointButtons[2 * i] = plusButton;
		m_jointButtons[2 * i + 1] = minusButton;
	}

	// Ligne verticale entre les deux groupes
	QFrame* line = new QFrame(this);
	line->setFrameShape(QFrame::VLine);
	line->setFrameShadow(QFrame::Sunken);
	layout->addWidget(line, 0, 1, 3, 1); // ligne verticale sur 3 lignes
}

void AppView::createIOBtns(QGridLayout* layout)
{
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 0; row < 4; ++row)
		{
			int index = col * 4 + row;

			QLabel* label = new QLabel(QString("IO %1:").arg(index + 1), this);
			label->setFixedWidth(30);
			QPushButton* inputBtn = new QPushButton("I", this);
			QPushButton* outputBtn = new QPushButton("O", this);
			inputBtn->setDisabled(true);
			outputBtn->setDisabled(true);

			inputBtn->setCheckable(true);
			outputBtn->setCheckable(true);

			inputBtn->setFixedSize(30, 30);
			outputBtn->setFixedSize(30, 30);

			QHBoxLayout* ioLayout = new QHBoxLayout();
			ioLayout->setContentsMargins(3, 0, 3, 0);
			ioLayout->addWidget(label);
			ioLayout->addWidget(inputBtn);
			ioLayout->addWidget(outputBtn);

			QWidget* ioWidget = new QWidget();
			ioWidget->setLayout(ioLayout);

			layout->addWidget(ioWidget, row, col * 2); // *2 car on insère des QFrame entre
			connect(inputBtn, &QPushButton::toggled, this, [this, index](bool checked) { emit inputToggled(static_cast<RobotKuka::IOInput>(index), checked); });
			connect(outputBtn, &QPushButton::toggled, this, [this, index](bool checked) { emit outputToggled(static_cast<RobotKuka::IOOutput>(index), checked); });
			
			m_ioButtons[2 * index] = inputBtn;
			m_ioButtons[2 * index + 1] = outputBtn;

			// Ligne verticale entre colonnes (sauf après la dernière)
			if (col < 3 && row == 0)
			{
				QFrame* line = new QFrame(this);
				line->setFrameShape(QFrame::VLine);
				line->setFrameShadow(QFrame::Sunken);
				layout->addWidget(line, 0, col * 2 + 1, 4, 1); // ligne verticale sur 4 lignes
			}
		}
	}
}

QGroupBox* AppView::createPoseGroup(const QString& title, QList<QLabel*>& labelsToFeed, QList<QLineEdit*>& lineEditsToFeed)
{
	auto* group = new QGroupBox(title, this);
	auto* layout = new QGridLayout();

	QStringList labels = { "X", "Y", "Z", "A", "B", "C" };

	for (int i = 0; i < 3; ++i)
	{
		// Partie gauche : X, Y, Z
		QLabel* labelL = new QLabel(labels[i], this);
		labelL->setMinimumWidth(20);
		labelL->setAlignment(Qt::AlignCenter);
		QLineEdit* editL = new QLineEdit(this);
		editL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		editL->setPlaceholderText("0.000");
		editL->setDisabled(true);
		layout->addWidget(labelL, i, 0);
		layout->addWidget(editL, i, 1);
		labelsToFeed[i] = labelL;
		lineEditsToFeed[i] = editL;

		// Partie droite : A, B, C
		QLabel* labelR = new QLabel(labels[i + 3], this);
		labelR->setAlignment(Qt::AlignCenter);
		labelR->setMinimumWidth(20);
		QLineEdit* editR = new QLineEdit(this);
		editR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		editR->setPlaceholderText("0.000");
		editR->setDisabled(true);
		layout->addWidget(labelR, i, 3);
		layout->addWidget(editR, i, 4);
		labelsToFeed[3 + i] = labelR;
		lineEditsToFeed[3 + i] = editR;
	}

	// Ligne verticale entre les deux blocs
	QFrame* line = new QFrame(this);
	line->setFrameShape(QFrame::VLine);
	line->setFrameShadow(QFrame::Sunken);
	layout->addWidget(line, 0, 2, 3, 1); // de ligne 0 à 2, colonne 2

	group->setLayout(layout);
	return group;
}

void AppView::switchConnectBtnToCancelBtn()
{
	if (m_connectButton->text() != "Cancel")
	{
		m_connectButton->setText("Cancel");
		disconnect(m_connectButton, &QPushButton::clicked, this, &AppView::onConnectButtonClicked);
		connect(m_connectButton, &QPushButton::clicked, this, &AppView::cancelConnectButtonClicked);
	}
}

void AppView::switchCancelBtnToConnectBtn()
{
	if (m_connectButton->text() != "Connect")
	{
		m_connectButton->setText("Connect");
		disconnect(m_connectButton, &QPushButton::clicked, this, &AppView::cancelConnectButtonClicked);
		connect(m_connectButton, &QPushButton::clicked, this, &AppView::onConnectButtonClicked);
	}
}

void AppView::setConnectionLabelText(const QString& text)
{
	if (text.isEmpty())
		clearConnectionLabelText();
	else
	{
		if (!m_connectionLabel)
		{
			m_connectionLabel = new QLabel(text, this);
			m_connectionLayout->addWidget(m_connectionLabel);
		}
		else
			m_connectionLabel->setText(text);
	}
}

void AppView::clearConnectionLabelText()
{
	if (m_connectionLabel) {
		m_connectionLabel->deleteLater();
		m_connectionLabel = nullptr;
	}
}

void AppView::setMoveAndIOButtonsEnabled(bool enabled) const
{
	for (auto& moveButton : m_axisButtons)
		moveButton->setEnabled(enabled);

	for (auto& jointButton : m_jointButtons)
		jointButton->setEnabled(enabled);

	for (auto& ioButton : m_ioButtons)
		ioButton->setEnabled(enabled);
}

void AppView::setMoveAndIOButtonsChecked(bool checked) const
{
	for (auto& moveButton : m_axisButtons)
		moveButton->setChecked(checked);

	for (auto& jointButton : m_jointButtons)
		jointButton->setChecked(checked);

	for (auto& ioButton : m_ioButtons)
		ioButton->setChecked(checked);
}

void AppView::setTimerIntervale(double freshRateHz)
{
	if (freshRateHz < 1.)
		freshRateHz = 1.;
	else if (freshRateHz >= 60.)
		freshRateHz = 60.;

	if (!Helper::fuzzyCompare(m_freshRateHz, freshRateHz))
	{
		m_freshRateHz = freshRateHz;
		m_uiTimer.setInterval(static_cast<int>(1000.0 / m_freshRateHz));
	}
}

void AppView::setIsJoggingInCartesian(bool isCartesian)
{
	if (m_isJoggingCartesian != isCartesian)
	{
		m_isJoggingCartesian = isCartesian;
		if (m_isJoggingCartesian)
		{
			m_poseLabels[0]->setText("X");
			m_poseLabels[1]->setText("Y");
			m_poseLabels[2]->setText("Z");
			m_poseLabels[3]->setText("A");
			m_poseLabels[4]->setText("B");
			m_poseLabels[5]->setText("C");

			m_deltaLabels[0]->setText("dX");
			m_deltaLabels[1]->setText("dY");
			m_deltaLabels[2]->setText("dZ");
			m_deltaLabels[3]->setText("dA");
			m_deltaLabels[4]->setText("dB");
			m_deltaLabels[5]->setText("dC");
		}
		else
		{
			m_poseLabels[0]->setText("J1");
			m_poseLabels[1]->setText("J2");
			m_poseLabels[2]->setText("J3");
			m_poseLabels[3]->setText("J4");
			m_poseLabels[4]->setText("J5");
			m_poseLabels[5]->setText("J6");

			m_deltaLabels[0]->setText("dJ1");
			m_deltaLabels[1]->setText("dJ2");
			m_deltaLabels[2]->setText("dJ3");
			m_deltaLabels[3]->setText("dJ4");
			m_deltaLabels[4]->setText("dJ5");
			m_deltaLabels[5]->setText("dJ6");
		}
		emit requestRefreshUI(m_isJoggingCartesian);

		emit isJoggingInCartesianChanged(m_isJoggingCartesian);
	}
}

void AppView::setIsMovingInRobotBase(bool isMovingInRobotBase)
{
	if (m_isMovingInRobotBase != isMovingInRobotBase)
	{
		m_isMovingInRobotBase = isMovingInRobotBase;
		emit isMovingInRobotBaseChanged(m_isMovingInRobotBase);
	}
}

void AppView::setConfig(const Config* config)
{
	if (config)
	{
		QList<ParameterBase*> params = config->getParameters();
		QList<const ParameterBase*> constParams;
		for (auto* param : params)
		{
			constParams.append(param);
		}
		m_parametersView->setParameters(constParams);
	}
}

void AppView::updatePose(double positions[6])
{
	for (int i = 0; i < 6; ++i) {
		m_poseLineEdits[i]->setText(QString::number(positions[i], 'f', 3));
	}
}

void AppView::updateDelta(double positions[6])
{
	for (int i = 0; i < 6; ++i) {
		m_deltaLineEdits[i]->setText(QString::number(positions[i], 'f', 3));
	}
}

void AppView::synchronizeIO(bool inputs[16], bool outputs[16])
{
	for (int i = 0; i < 16; i++)
	{
		m_ioButtons[2 * i]->setChecked(inputs[i]);
		m_ioButtons[2 * i + 1]->setChecked(outputs[i]);
	}
}

void AppView::refreshUI()
{
	emit requestRefreshUI(m_isJoggingCartesian);
}

void AppView::onConnectButtonClicked()
{
	emit connectButtonClicked();
}

void AppView::onCancelButtonClicked()
{
	emit cancelConnectButtonClicked();
}

void AppView::onDisconnectButtonClicked()
{
	m_disconnectButton->setDisabled(true);
	emit disconnectButtonClicked();
}

void AppView::onStartButtonClicked()
{
	m_startButton->setDisabled(true);
	emit startButtonClicked();
}

void AppView::onStopButtonClicked()
{
	m_startButton->setDisabled(true);
	m_stopButton->setDisabled(true);
	emit stopButtonClicked();
}

void AppView::onBaseComboBoxChanged(int index)
{
	setIsMovingInRobotBase(index == 0); // 0 = BASE, 1 = TOOL
	emit isMovingInRobotBaseChanged(m_isMovingInRobotBase);
}

void AppView::onMoveTabChanged(int index)
{
	setIsJoggingInCartesian(index == 0);
}

void AppView::onRobotStatusChanged(RobotKuka::Status status)
{
	// remise a zero
	m_connectButton->setEnabled(false);
	m_disconnectButton->setEnabled(false);
	m_startButton->setEnabled(false);
	m_stopButton->setEnabled(false);
	setMoveAndIOButtonsEnabled(false);
	setMoveAndIOButtonsChecked(false);
	m_statusLabel->setText(RobotKuka::toString(status));
	m_isReadyToMove = false;
	// -----------------------------------

	switch (status)
	{
	case RobotKuka::Status::Ready:
		switchCancelBtnToConnectBtn();
		m_connectButton->setEnabled(true);
		break;
	case RobotKuka::Status::WaitingRobotConnection:
		setConnectionLabelText("Waiting for robot");
		switchConnectBtnToCancelBtn();
		m_connectButton->setEnabled(true);
		break;
	case RobotKuka::Status::Connected:
		switchCancelBtnToConnectBtn();
		m_disconnectButton->setEnabled(true);
		m_startButton->setEnabled(true);
		clearConnectionLabelText();
		break;
	case RobotKuka::Status::ReadyToMove:
		m_isReadyToMove = true;
		m_disconnectButton->setEnabled(true);
		m_stopButton->setEnabled(true);
		setMoveAndIOButtonsEnabled(true);
		break;
	case RobotKuka::Status::Error:
		switchCancelBtnToConnectBtn();
		m_connectButton->setEnabled(true);
		break;
	default:
		break;
	}
}

void AppView::onRobotStateChanged(RobotKuka::RobotState state)
{
	m_robotStateLabel->setText(RobotKuka::toString(state));
}

void AppView::onRobotConnected()
{
	emit requestRefreshUI(m_isJoggingCartesian);
}

void AppView::onRobotDisconnected()
{
	m_uiTimer.stop(); // to be sure
	QTimer::singleShot(100, [this]() {
		for (int i = 0; i < 6; i++)
		{
			m_poseLineEdits[i]->clear();
			m_deltaLineEdits[i]->clear();
		}
		});
}

void AppView::onRobotStarted()
{
	// start timer
	m_uiTimer.start();
}

void AppView::onRobotStopped()
{
	// stop timer
	m_uiTimer.stop();
}

void AppView::onConnectionTimeRemainingChanged(quint16 seconds)
{
	setConnectionLabelText(QString("Waiting for robot (%1 s)").arg(seconds));
}

void AppView::onFreshRateChanged(double freshRateHz)
{
	setTimerIntervale(freshRateHz);
}
