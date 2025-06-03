#pragma once
#include "FrameViewer.h"
#include "ParametersView.h"
#include "CameraConfig.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class DeviceView : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceView(QWidget* parent = nullptr);

    void setLightInfo(const QString& comPort, int relay);   // update labels
    void setButtonsState(bool enabled);
    void setCameraConfig(const CameraConfig* cameraConfig);

signals:
    void lightOnRequested();
    void lightOffRequested();

private:
    void buildUi();

    // cached widgets
	FrameViewer* m_frameViewer{ nullptr };
	ParametersView* m_parametersView{ nullptr };
    QLabel* m_comLabel{ nullptr };
    QLabel* m_relayLabel{ nullptr };
    QPushButton* m_onButton{ nullptr };
    QPushButton* m_offButton{ nullptr };
};
