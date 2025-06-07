#include "AppView.h"

AppView::AppView(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

void AppView::setupUI()
{
    auto* layout = new QGridLayout(this);

    createActionButtons(layout);
    createMovementButtons(layout);

    setLayout(layout);
}

void AppView::createActionButtons(QGridLayout* layout)
{
    m_connectButton = new QPushButton("Connect", this);
    m_disconnectButton = new QPushButton("Disconnect", this);
    m_startButton = new QPushButton("Start", this);
    m_stopButton = new QPushButton("Stop", this);

    layout->addWidget(m_connectButton, 0, 0);
    layout->addWidget(m_disconnectButton, 0, 1);
    layout->addWidget(m_startButton, 0, 2);
    layout->addWidget(m_stopButton, 0, 3);

    connect(m_connectButton, &QPushButton::clicked, this, &AppView::connectButtonClicked);
    connect(m_disconnectButton, &QPushButton::clicked, this, &AppView::disconnectButtonClicked);
    connect(m_startButton, &QPushButton::clicked, this, &AppView::startButtonClicked);
    connect(m_stopButton, &QPushButton::clicked, this, &AppView::stopButtonClicked);
}

void AppView::createMovementButtons(QGridLayout* layout)
{
    // Create and place buttons with directions
    QMap<QString, QPoint> positions = {
        { "up",       {1, 1} },
        { "down",     {3, 1} },
        { "left",     {2, 0} },
        { "right",    {2, 2} },
        { "forward",  {1, 3} },
        { "backward", {3, 3} }
    };

    for (auto it = positions.begin(); it != positions.end(); ++it)
    {
        const QString& direction = it.key();
        const QPoint& pos = it.value();

        QPushButton* button = new QPushButton(direction.toUpper(), this);
        m_movementButtons[direction] = button;
        layout->addWidget(button, pos.x(), pos.y());

        setupMovementSignals(button, direction);
    }
}

void AppView::setupMovementSignals(QPushButton* button, const QString& direction)
{
    connect(button, &QPushButton::pressed, [this, direction]() {
        emit movementPressed(direction);
        });
    connect(button, &QPushButton::released, [this, direction]() {
        emit movementReleased(direction);
        });
}
