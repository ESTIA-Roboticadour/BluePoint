#pragma once
#include "WidgetControllerBase.h"
#include "AppModel.h"
#include "AppView.h"
#include "RobotKuka.h"

#include <QObject>
#include <QString>
#include <QMatrix4x4>

class AppController : public WidgetControllerBase
{
	Q_OBJECT
public:
	explicit AppController(AppModel* model, AppView* view, QObject* parent = nullptr);
	~AppController() override;

private slots:
	// Inherited via WidgetControllerBase
	void onViewDestroyed() override;
	void onViewRequestNewPose();
	void onViewRequestNewDelta();

	void onModelReleased();

	void onErrorOccurred(const QString& msg);

private:
	void setupConnections();
	void removeConnections();

private:
	AppModel* m_model{ nullptr };
	AppView* m_view{ nullptr };
};

