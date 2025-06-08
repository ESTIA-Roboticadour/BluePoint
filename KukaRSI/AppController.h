#pragma once
#include "WidgetControllerBase.h"
#include "AppModel.h"
#include "AppView.h"

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

	void onModelReleased();

	void onRobotStateChanged();
	void onRobotPoseChanged(const QMatrix4x4& pose);
	void onErrorOccurred(const QString& msg);

private:
	void setupConnections();

private:
	AppModel* m_model{ nullptr };
	AppView* m_view{ nullptr };
};

