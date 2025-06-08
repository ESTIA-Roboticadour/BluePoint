#pragma once
#include "MovementDirection.h"
#include "ParametersView.h"
#include "Config.h"

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QMap>
#include <QLineEdit>

class AppView : public QWidget
{
    Q_OBJECT

public:
    explicit AppView(QWidget* parent = nullptr);

    void setConfig(const Config* config);

public slots:
    void updatePose(double positions[6]);
    void updateDelta(double positions[6]);

private slots:
    void handleMovementPressed();
    void handleMovementReleased();

private:
    void setupUI();
    void createMovementButtons(QGridLayout* layout);
    void setupMovementSignals(QPushButton* button, MovementDirection direction) const;
    QGroupBox* createPoseGroup(const QString& title, QList<QLineEdit*>& listToFeed);

signals:
    void connectButtonClicked();
    void disconnectButtonClicked();
    void startButtonClicked();
    void stopButtonClicked();

    void movementPressed(MovementDirection direction);
    void movementReleased(MovementDirection direction);

private:
    QPushButton* m_connectButton;
    QPushButton* m_disconnectButton;
    QPushButton* m_startButton;
    QPushButton* m_stopButton;
    ParametersView* m_parametersView;
    QList<QLineEdit*> m_poseLineEdits;
    QList<QLineEdit*> m_deltaLineEdits;
    QMap<MovementDirection, QPushButton*> m_movementButtons;
};
