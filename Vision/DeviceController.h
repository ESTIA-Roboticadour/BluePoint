#pragma once
#include <QObject>

#include "WidgetControllerBase.h"
#include "DeviceModel.h"
#include "DeviceView.h"

class DeviceController : public WidgetControllerBase
{
	Q_OBJECT

public:
	explicit DeviceController(DeviceModel* model, DeviceView* view, QObject* parent = nullptr);
	~DeviceController() override;

private slots:
	// Inherited via WidgetControllerBase
	void onViewDestroyed() override;

	void onModelReleased();

private:
	void setupConnections();

private:
	DeviceModel* m_model{ nullptr };
	DeviceView* m_view{ nullptr };
};
