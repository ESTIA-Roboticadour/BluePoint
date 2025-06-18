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
	m_movementButtons(),
	m_uiTimer(),
	m_freshRateHz(20),
	m_jointButtons(),
	m_ioButtons(),
	m_isReadyToMove(false),
	m_isJoggingCartesian(true),
	m_pressedKeys(),
	m_monitoredKeys(),
	m_isAzerty(true)
{
	feedMonitoredKeys();

	setupUI();
	m_uiTimer.setInterval(static_cast<int>(1000.0 / m_freshRateHz));
	connect(&m_uiTimer, &QTimer::timeout, this, &AppView::refreshUI);
}

void AppView::feedMonitoredKeys()
{
	m_isAzerty = Helper::detectKeyboardLayout() == "azerty";
	m_monitoredKeys = m_isAzerty ?
		QSet<Qt::Key> { Qt::Key_Z, Qt::Key_Q, Qt::Key_S, Qt::Key_D, Qt::Key_F, Qt::Key_B } :
		QSet<Qt::Key>{ Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D, Qt::Key_F, Qt::Key_B };
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
	baseComboBox->addItems({ "TOOL", "WORLD" });
	baseComboBox->setCurrentText("TOOL");
	baseComboBox->setDisabled(true);
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

	auto* positionGroup = createPoseGroup("Position", m_poseLineEdits);
	auto* deltaGroup = createPoseGroup("Delta", m_deltaLineEdits);

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
	QMap<RobotKuka::MovementDirection, QPoint> positions = {
		{ RobotKuka::MovementDirection::Up,       {0, 1} },
		{ RobotKuka::MovementDirection::Down,     {2, 1} },
		{ RobotKuka::MovementDirection::Left,     {1, 0} },
		{ RobotKuka::MovementDirection::Right,    {1, 2} },
	};

	QStringList content{
		QStringLiteral(u"\u2191"), // up
		QStringLiteral(u"\u2193"), // down
		QStringLiteral(u"\u2190"), // left
		QStringLiteral(u"\u2192")  // right
	};

	int i = 0;
	for (auto it = positions.begin(); it != positions.end(); ++it)
	{
		RobotKuka::MovementDirection direction = it.key();
		const QPoint& pos = it.value();

		QPushButton* button = new QPushButton(content[i++], this);
		button->setFixedSize(30, 30);
		button->setCheckable(true);
		button->setEnabled(false);
		m_movementButtons[direction] = button;
		layout->addWidget(button, pos.x(), pos.y());

		connect(button, &QPushButton::pressed, this, [this, direction]() { emit onCartesianMovementButtonPressed(direction); });
		connect(button, &QPushButton::released, this, [this, direction]() { emit onCartesianMovementButtonReleased(direction); });
	}

	// Ligne verticale entre le bloc central et F/B
	QFrame* separator = new QFrame(this);
	separator->setFrameShape(QFrame::VLine);
	separator->setFrameShadow(QFrame::Sunken);

	layout->addWidget(separator, 0, 3, 3, 1); // ligne verticale entre col 2 et 4

	// Ajout des boutons F/B dans un layout horizontal
	QStringList fbLabels{ "F", "B" };
	RobotKuka::MovementDirection fbDirections[] = {
		RobotKuka::MovementDirection::Forward,
		RobotKuka::MovementDirection::Backward
	};

	for (int j = 0; j < 2; ++j)
	{
		QPushButton* button = new QPushButton(fbLabels[j], this);
		button->setFixedSize(30, 30);
		button->setCheckable(true);
		button->setEnabled(false);
		RobotKuka::MovementDirection direction = fbDirections[j];
		m_movementButtons[direction] = button;
		layout->addWidget(button, j * 2, 4); // col 4 après la ligne verticale

		connect(button, &QPushButton::pressed, this, [this, direction]() { emit onCartesianMovementButtonPressed(direction); });
		connect(button, &QPushButton::released, this, [this, direction]() { emit onCartesianMovementButtonReleased(direction); });
	}
}

void AppView::createJointControlButtons(QGridLayout* layout)
{
	for (int i = 0; i < 6; ++i)
	{
		QString label = QString("J%1").arg(i + 1);
		QLabel* jointLabel = new QLabel(label, this);

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
		m_jointButtons.append(plusButton);
		m_jointButtons.append(minusButton);
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
			m_ioButtons.append(inputBtn);
			m_ioButtons.append(outputBtn);

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

QGroupBox* AppView::createPoseGroup(const QString& title, QList<QLineEdit*>& listToFeed)
{
	auto* group = new QGroupBox(title, this);
	auto* layout = new QGridLayout();

	QStringList labels = { "X", "Y", "Z", "A", "B", "C" };

	for (int i = 0; i < 3; ++i)
	{
		// Partie gauche : X, Y, Z
		QLabel* labelL = new QLabel(labels[i], this);
		QLineEdit* editL = new QLineEdit(this);
		editL->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		editL->setPlaceholderText("0.000");
		editL->setDisabled(true);
		layout->addWidget(labelL, i, 0);
		layout->addWidget(editL, i, 1);
		listToFeed[i] = editL;

		// Partie droite : A, B, C
		QLabel* labelR = new QLabel(labels[i + 3], this);
		QLineEdit* editR = new QLineEdit(this);
		editR->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		editR->setPlaceholderText("0.000");
		editR->setDisabled(true);
		layout->addWidget(labelR, i, 3);
		layout->addWidget(editR, i, 4);
		listToFeed[3 + i] = editR;
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
	for (auto& moveButton : m_movementButtons)
		moveButton->setEnabled(enabled);

	for (auto& jointButton : m_jointButtons)
		jointButton->setEnabled(enabled);

	for (auto& ioButton : m_ioButtons)
		ioButton->setEnabled(enabled);
}

void AppView::setMoveAndIOButtonsChecked(bool checked) const
{
	for (auto& moveButton : m_movementButtons)
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

void AppView::setJoggingMode(bool isCartesian)
{
	if (m_isJoggingCartesian != isCartesian)
	{
		m_isJoggingCartesian = isCartesian;
		emit joggingModeChanged(m_isJoggingCartesian);
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
	emit requestNewPose();
	emit requestNewDelta();
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
	m_stopButton->setDisabled(true);
	emit stopButtonClicked();
}

void AppView::onMoveTabChanged(int index)
{
	setJoggingMode(index == 0);
	for (auto& pressedKey : m_pressedKeys)
		handleKeyReleased(pressedKey);
	m_pressedKeys.clear();
}

void AppView::onCartesianMovementButtonPressed(RobotKuka::MovementDirection direction)
{
	bool keyAlreadyPressed = false;

	switch (direction)
	{
	case RobotKuka::Up:
		keyAlreadyPressed = isKeyPressed(m_isAzerty ? Qt::Key_Z : Qt::Key_W);
		break;
	case RobotKuka::Down:
		keyAlreadyPressed = isKeyPressed(Qt::Key_S);
		break;
	case RobotKuka::Left:
		keyAlreadyPressed = isKeyPressed(m_isAzerty ? Qt::Key_Q : Qt::Key_A);
		break;
	case RobotKuka::Right:
		keyAlreadyPressed = isKeyPressed(Qt::Key_D);
		break;
	case RobotKuka::Forward:
		keyAlreadyPressed = isKeyPressed(Qt::Key_F);
		break;
	case RobotKuka::Backward:
		keyAlreadyPressed = isKeyPressed(Qt::Key_B);
		break;
	default:
		qWarning() << RobotKuka::toString(direction) + " not implemented";
		break;
	}

	if (!keyAlreadyPressed)
	{
		m_movementButtons[direction]->setChecked(true);
		emit cartesianMovementPressed(direction);
	}
}

void AppView::onCartesianMovementButtonReleased(RobotKuka::MovementDirection direction)
{
	bool keyStillPressed = false;

	switch (direction)
	{
	case RobotKuka::Up:
		keyStillPressed = isKeyPressed(m_isAzerty ? Qt::Key_Z : Qt::Key_W);
		break;
	case RobotKuka::Down:
		keyStillPressed = isKeyPressed(Qt::Key_S);;
		break;
	case RobotKuka::Left:
		keyStillPressed = isKeyPressed(m_isAzerty ? Qt::Key_Q : Qt::Key_A);
		break;
	case RobotKuka::Right:
		keyStillPressed = isKeyPressed(Qt::Key_D);;
		break;
	case RobotKuka::Forward:
		keyStillPressed = isKeyPressed(Qt::Key_F);
		break;
	case RobotKuka::Backward:
		keyStillPressed = isKeyPressed(Qt::Key_B);
		break;
	default:
		qWarning() << RobotKuka::toString(direction) + " not implemented";
		break;
	}

	if (!keyStillPressed)
	{
		m_movementButtons[direction]->setChecked(false);
		emit cartesianMovementReleased(direction);
	}
	else
	{
		m_movementButtons[direction]->setChecked(true);
	}
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
	clearConnectionLabelText();
	m_pressedKeys.clear();
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
	emit requestNewPose();
	emit requestNewDelta();
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

void AppView::keyPressEvent(QKeyEvent* event)
{
	if (m_isReadyToMove && m_isJoggingCartesian)
	{
		Qt::Key key = static_cast<Qt::Key>(event->key());

		if (!event->isAutoRepeat() && m_monitoredKeys.contains(key)) {
			m_pressedKeys.insert(key);
			handleKeyPressed(key);
		}
	}
}

void AppView::keyReleaseEvent(QKeyEvent* event)
{
	if (m_isReadyToMove && m_isJoggingCartesian)
	{
		Qt::Key key = static_cast<Qt::Key>(event->key());

		if (!event->isAutoRepeat() && m_monitoredKeys.contains(key)) {
			m_pressedKeys.remove(key);
			handleKeyReleased(key);
		}
	}
}

void AppView::handleKeyPressed(Qt::Key key)
{
	RobotKuka::MovementDirection movementDirection;
	switch (key)
	{
	case Qt::Key_Z: // azerty case
	case Qt::Key_W: // qwerty case
		movementDirection = RobotKuka::MovementDirection::Up;
		break;
	case Qt::Key_Q: // azerty case
	case Qt::Key_A: // qwerty case
		movementDirection = RobotKuka::MovementDirection::Left;
		break;
	case Qt::Key_S:
		movementDirection = RobotKuka::MovementDirection::Down;
		break;
	case Qt::Key_D:
		movementDirection = RobotKuka::MovementDirection::Right;
		break;
	case Qt::Key_F:
		movementDirection = RobotKuka::MovementDirection::Forward;
		break;
	case Qt::Key_B:
		movementDirection = RobotKuka::MovementDirection::Backward;
		break;
	default:
		return; // block next if case if not supported
	}

	if (!m_movementButtons[movementDirection]->isDown()) // button is not pressed
	{
		m_movementButtons[movementDirection]->setChecked(true); // set ui as button was pressed
		emit cartesianMovementPressed(movementDirection);
	}
}

void AppView::handleKeyReleased(Qt::Key key)
{
	RobotKuka::MovementDirection movementDirection;
	switch (key)
	{
	case Qt::Key_Z: // azerty case
	case Qt::Key_W: // qwerty case
		movementDirection = RobotKuka::MovementDirection::Up;
		break;
	case Qt::Key_Q: // azerty case
	case Qt::Key_A: // qwerty case
		movementDirection = RobotKuka::MovementDirection::Left;
		break;
	case Qt::Key_S:
		movementDirection = RobotKuka::MovementDirection::Down;
		break;
	case Qt::Key_D:
		movementDirection = RobotKuka::MovementDirection::Right;
		break;
	case Qt::Key_F:
		movementDirection = RobotKuka::MovementDirection::Forward;
		break;
	case Qt::Key_B:
		movementDirection = RobotKuka::MovementDirection::Backward;
		break;
	default:
		return; // block next if case if not supported
	}

	if (!m_movementButtons[movementDirection]->isDown()) // button is not pressed
	{
		m_movementButtons[movementDirection]->setChecked(false); // set ui as button was released
		emit cartesianMovementReleased(movementDirection);
	}
}
