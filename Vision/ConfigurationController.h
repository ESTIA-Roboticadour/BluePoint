#pragma once
#include "WidgetControllerBase.h"
#include "ConfigurationModel.h"
#include "ConfigurationView.h"

#include <QObject>
#include <QString>

class ConfigurationController : public WidgetControllerBase
{
	Q_OBJECT
public:
	explicit ConfigurationController(ConfigurationModel* model, ConfigurationView* view, QObject* parent = nullptr);
	~ConfigurationController() override;

private slots:
	// Inherited via WidgetControllerBase
	void onViewDestroyed() override;

	void onModelReleased();

private:
	void setupConnections();

private:
	ConfigurationModel* m_model{ nullptr };
	ConfigurationView* m_view{ nullptr };
};
