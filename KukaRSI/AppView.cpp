#include "AppView.h"
#include "TransparentScrollArea.h"

#include <QHBoxLayout>
#include <QSizePolicy>
#include <QStringList>
#include <QList>

AppView::AppView(QWidget* parent) :
	TransparentScrollArea(parent),
	m_poseLineEdits(),
	m_deltaLineEdits(),
	m_movementButtons(),
	m_uiTimer(),
	m_freshRateHz(20)
{
	setupUI();
	m_uiTimer.setInterval(static_cast<int>(1000.0 / m_freshRateHz));
	connect(&m_uiTimer, &QTimer::timeout, this, &AppView::refreshUI);
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

	// 2eme ligne : Groupe "Status"
	auto* statusGroup = new QGroupBox("Status", this);
	statusGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	auto* statusLayout = new QHBoxLayout();
	m_statusLabel = new QLabel("", statusGroup);
	statusLayout->addWidget(new QLabel("Status:", statusGroup));
	statusLayout->addWidget(m_statusLabel);
	statusGroup->setLayout(statusLayout);
	leftLayout->addWidget(statusGroup);

	leftLayout->addStretch();

	// Droite : colonne
	auto* rightLayout = new QVBoxLayout();

	// Groupe "Connection"
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

	// Ligne 2 : Move
	auto* moveGroup = new QGroupBox("Move", this);
	moveGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	auto* moveLayout = new QGridLayout();
	moveGroup->setLayout(moveLayout);
	moveLayout->setAlignment(Qt::AlignLeft);

	controlLayout->addWidget(moveGroup);
	createMovementButtons(moveLayout);

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
	mainLayout->addLayout(rightLayout, 1);

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
		{ RobotKuka::MovementDirection::Forward,  {0, 3} },
		{ RobotKuka::MovementDirection::Backward, {2, 3} }
	};

	QStringList content{
		QStringLiteral(u"\u2191"), // up
		QStringLiteral(u"\u2193"), // down
		QStringLiteral(u"\u2190"), // left
		QStringLiteral(u"\u2192"), // right
		QStringLiteral(u"\u0046"), // F
		QStringLiteral(u"\u0042")  // B
	};

	int i = 0;
	for (auto it = positions.begin(); it != positions.end(); ++it)
	{
		RobotKuka::MovementDirection direction = it.key();
		const QPoint& pos = it.value();

		QPushButton* button = new QPushButton(content[i++], this);
		button->setFixedSize(30, 30);
		button->setEnabled(false);
		m_movementButtons[direction] = button;
		layout->addWidget(button, pos.x(), pos.y());

		setupMovementSignals(button, direction);
	}
}

void AppView::setupMovementSignals(QPushButton* button, RobotKuka::MovementDirection direction) const
{
	button->setProperty("movementDirection", QVariant::fromValue(direction));
	connect(button, &QPushButton::pressed, this, &AppView::handleMovementPressed);
	connect(button, &QPushButton::released, this, &AppView::handleMovementReleased);
}

QGroupBox* AppView::createPoseGroup(const QString& title, QList<QLineEdit*>& listToFeed)
{
	listToFeed.clear();

	auto* group = new QGroupBox(title, this);
	auto* layout = new QGridLayout();

	QStringList labels = { "X", "Y", "Z", "A", "B", "C" };
	for (int i = 0; i < labels.size(); ++i) {
		QLabel* label = new QLabel(labels[i], this);
		QLineEdit* lineEdit = new QLineEdit(this);
		lineEdit->setPlaceholderText("0.000");
		lineEdit->setDisabled(true);
		layout->addWidget(label, i, 0);
		layout->addWidget(lineEdit, i, 1);
		listToFeed.append(lineEdit);
	}

	group->setLayout(layout);
	return group;
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

void AppView::setTimerIntervale(int freshRateHz)
{
	if (freshRateHz < 1.)
		freshRateHz = 1.;
	else if (freshRateHz >= 60.)
		freshRateHz = 60.;

	if (m_freshRateHz != freshRateHz) // qFuzzyCompare ?
	{
		m_freshRateHz = freshRateHz;
		m_uiTimer.setInterval(static_cast<int>(1000.0 / m_freshRateHz));
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

void AppView::handleMovementPressed()
{
	auto* button = qobject_cast<QPushButton*>(sender());
	if (!button) return;

	RobotKuka::MovementDirection direction = button->property("movementDirection").value<RobotKuka::MovementDirection>();
	emit movementPressed(direction);
}

void AppView::handleMovementReleased()
{
	auto* button = qobject_cast<QPushButton*>(sender());
	if (!button) return;

	RobotKuka::MovementDirection direction = button->property("movementDirection").value<RobotKuka::MovementDirection>();
	emit movementReleased(direction);
}

void AppView::refreshUI()
{
	emit requestNewPose();
	emit requestNewDelta();
}

void AppView::onConnectButtonClicked()
{
	m_connectButton->setDisabled(true);
	emit connectButtonClicked();
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

void AppView::onRobotStateChanged(RobotKuka::Status status)
{
	m_connectButton->setEnabled(false);
	m_disconnectButton->setEnabled(false);
	m_startButton->setEnabled(false);
	m_stopButton->setEnabled(false);
	m_statusLabel->setText(RobotKuka::toQString(status));
	clearConnectionLabelText();

	switch (status)
	{
	case RobotKuka::Ready:
		m_connectButton->setEnabled(true);
		break;
	case RobotKuka::WaitingRobotConnection:
		setConnectionLabelText("Waiting for robot");
		break;
	case RobotKuka::Connected:
		m_disconnectButton->setEnabled(true);
		m_startButton->setEnabled(true);
		break;
	case RobotKuka::Moving:
		m_disconnectButton->setEnabled(true);
		m_stopButton->setEnabled(true);
		break;
	case RobotKuka::Error:
		m_connectButton->setEnabled(true);
		break;
	default:
		break;
	}
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

void AppView::onConnectionTimeRemainingChanged(int seconds)
{
	setConnectionLabelText(QString("Waiting for robot (%1 s)").arg(seconds));
}

void AppView::onFreshRateChanged(double freshRateHz)
{
	setTimerIntervale(freshRateHz);
}
