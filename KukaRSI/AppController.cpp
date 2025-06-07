#include "AppController.h"

AppController::AppController(AppModel* model, AppView* view, QObject* parent):
	WidgetControllerBase(model, view, parent),
	m_view(view),
	m_model(model)
{
	setupConnections();
}

AppController::~AppController()
{
}

void AppController::onModelReleased()
{
	deleteLater();
}

void AppController::setupConnections()
{
	connect(m_model, &AppModel::released, this, &AppController::onModelReleased);

	connect(m_view, &AppView::connectButtonClicked, m_model, &AppModel::connectToRobot);
	connect(m_view, &AppView::disconnectButtonClicked, m_model, &AppModel::disconnectFromRobot);
	connect(m_view, &AppView::startButtonClicked, m_model, &AppModel::startRobot);
	connect(m_view, &AppView::stopButtonClicked, m_model, &AppModel::stopRobot);

	connect(m_view, &AppView::movementPressed, this, &AppController::onMovementPressed);
	connect(m_view, &AppView::movementReleased, this, &AppController::onMovementReleased);
		
	// Connexions AppModel -> AppView ou autres
	connect(m_model, &AppModel::robotStateChanged, this, &AppController::onRobotStateChanged);
	connect(m_model, &AppModel::robotPoseChanged, this, &AppController::onRobotPoseChanged);
	connect(m_model, &AppModel::errorOccurred, this, &AppController::onErrorOccurred);
}

void AppController::onViewDestroyed()
{
	m_view = nullptr;
	m_model->release();
}

void AppController::onMovementPressed(const QString& dir)
{
	if (m_model && m_model->robot())
		m_model->robot()->move(dir);
}

void AppController::onMovementReleased(const QString& dir)
{
	Q_UNUSED(dir);
	if (m_model && m_model->robot())
		m_model->robot()->stopMovement();
}

void AppController::onRobotStateChanged()
{
}

void AppController::onRobotPoseChanged(const QMatrix4x4& pose)
{
}

void AppController::onErrorOccurred(const QString& msg)
{
	qWarning() << ("[AppController] Error from model: " + msg);
}
