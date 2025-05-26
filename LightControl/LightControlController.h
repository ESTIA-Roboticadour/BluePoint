#pragma once

#include "LightControlModel.h"
#include "LightControlWindow.h"
#include <QObject>
#include <QString>

class LightControlController : public QObject
{
    Q_OBJECT

public:
    explicit LightControlController(LightControl* model, LightControlWindow* view, QObject* parent=nullptr);
    ~LightControlController();

private slots:
    void onViewPortSelectedChanged(const QString& portName);
    void onModelDisconnected();
    void onModelConnected(const QString& portName);
    void onModelConnectionFailed(const QString& portName, const QString& error);

private:
    void getAvailablePorts() const;
    void autoConnect() const;

private:
    LightControl* m_model;
    LightControlWindow* m_view;
};
