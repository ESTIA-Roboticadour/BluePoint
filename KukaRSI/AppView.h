#pragma once
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class AppView : public QWidget
{
    Q_OBJECT

public:
    explicit AppView(QWidget* parent = nullptr);

signals:
    void connectButtonClicked();
    void disconnectButtonClicked();
    void startButtonClicked();
    void stopButtonClicked();

    void movementPressed(const QString& direction);
    void movementReleased(const QString& direction);

private:
    void setupUI();
    void createActionButtons(QGridLayout* layout);
    void createMovementButtons(QGridLayout* layout);
    void setupMovementSignals(QPushButton* button, const QString& direction);

    QPushButton* m_connectButton;
    QPushButton* m_disconnectButton;
    QPushButton* m_startButton;
    QPushButton* m_stopButton;

    QMap<QString, QPushButton*> m_movementButtons;
};

