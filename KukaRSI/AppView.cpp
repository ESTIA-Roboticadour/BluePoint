#include "AppView.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QStringList>
#include <QList>

AppView::AppView(QWidget* parent) :
    QWidget(parent),
    m_connectButton(nullptr),
    m_disconnectButton(nullptr),
    m_startButton(nullptr),
    m_stopButton(nullptr),
    m_parametersView(nullptr),
    m_poseLineEdits(),
    m_deltaLineEdits(),
    m_movementButtons()
{
    setupUI();
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

void AppView::setupUI()
{
    auto* mainLayout = new QHBoxLayout(this);

    // Groupe "Robot"
    auto* robotGroup = new QGroupBox("Robot", this);
    auto* robotLayout = new QVBoxLayout(robotGroup);

    m_parametersView = new ParametersView(robotGroup);
    robotLayout->addWidget(m_parametersView);

    robotGroup->setLayout(robotLayout);
    mainLayout->addWidget(robotGroup);

    // Droite : colonne
    auto* rightLayout = new QVBoxLayout();

    // Groupe "Connection"
    auto* connectionGroup = new QGroupBox("Connection", this);
    connectionGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    auto* connectionLayout = new QHBoxLayout();
    m_connectButton = new QPushButton("Connect", this);
    m_disconnectButton = new QPushButton("Disconnect", this);
    m_connectButton->setEnabled(false);
    m_disconnectButton->setEnabled(false);
    connectionLayout->addWidget(m_connectButton);
    connectionLayout->addWidget(m_disconnectButton);
    connectionLayout->addStretch();
    connectionGroup->setLayout(connectionLayout);
    rightLayout->addWidget(connectionGroup);
    rightLayout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed));

    // Groupe "Control"
    auto* controlGroup = new QGroupBox("Control", this);
    controlGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto* controlLayout = new QVBoxLayout();

    // Ligne 1 : Start / Stop
    auto* startStopLayout = new QHBoxLayout();
    m_startButton = new QPushButton("Start", this);
    m_stopButton = new QPushButton("Stop", this);
    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(false);
    startStopLayout->addWidget(m_startButton);
    startStopLayout->addWidget(m_stopButton);
    startStopLayout->addStretch();
    controlLayout->addLayout(startStopLayout);

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
    controlLayout->addStretch();

    controlGroup->setLayout(controlLayout);
    rightLayout->addWidget(controlGroup);

    mainLayout->addLayout(rightLayout);

    // Connexions
    connect(m_connectButton, &QPushButton::clicked, this, &AppView::connectButtonClicked);
    connect(m_disconnectButton, &QPushButton::clicked, this, &AppView::disconnectButtonClicked);
    connect(m_startButton, &QPushButton::clicked, this, &AppView::startButtonClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &AppView::stopButtonClicked);

    setLayout(mainLayout);
}

void AppView::createMovementButtons(QGridLayout* layout)
{
    QMap<MovementDirection, QPoint> positions = {
        { MovementDirection::Up,       {0, 1} },
        { MovementDirection::Down,     {2, 1} },
        { MovementDirection::Left,     {1, 0} },
        { MovementDirection::Right,    {1, 2} },
        { MovementDirection::Forward,  {0, 3} },
        { MovementDirection::Backward, {2, 3} }
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
        MovementDirection direction = it.key();
        const QPoint& pos = it.value();

        QPushButton* button = new QPushButton(content[i++], this);
        button->setFixedSize(30, 30);
        button->setEnabled(false);
        m_movementButtons[direction] = button;
        layout->addWidget(button, pos.x(), pos.y());

        setupMovementSignals(button, direction);
    }
}

void AppView::setupMovementSignals(QPushButton* button, MovementDirection direction) const
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

void AppView::handleMovementPressed()
{
    auto* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    MovementDirection direction = button->property("movementDirection").value<MovementDirection>();
    emit movementPressed(direction);
}

void AppView::handleMovementReleased()
{
    auto* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    MovementDirection direction = button->property("movementDirection").value<MovementDirection>();
    emit movementReleased(direction);
}
