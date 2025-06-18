#include "AppController.h"
#include <QTimer>

AppController::AppController(AppModel* model, AppView* view, QObject* parent):
	WidgetControllerBase(model, view, parent),
	m_view(view),
	m_model(model)
{
	setupConnections();
	m_view->setConfig(m_model->getConfig());

	m_view->onRobotStatusChanged(m_model->getRobotStatus());
	m_view->onRobotStateChanged(m_model->getRobotState());

	//QTimer::singleShot(3000, [=]() { m_view->onRobotStatusChanged(RobotKuka::Status::Connected); });  // TODO : to delete
}

AppController::~AppController()
{
}

void AppController::onViewDestroyed()
{
	removeConnections();
	m_view = nullptr;
	m_model->release();
}

void AppController::onViewRequestNewPose()
{
	double currentPose[6];
	m_model->getCurrentPose(currentPose);
	m_view->updatePose(currentPose);
}

void AppController::onViewRequestNewDelta()
{
	double currentDelta[6];
	m_model->getCurrentDelta(currentDelta);
	m_view->updateDelta(currentDelta);
}

void AppController::onModelReleased()
{
	deleteLater();
}

void AppController::setupConnections()
{
	connect(m_model, &AppModel::released, this, &AppController::onModelReleased);

	// Connexions AppView -> AppModel  ou autres
	connect(m_view, &AppView::connectButtonClicked, m_model, &AppModel::connectToRobot);
	connect(m_view, &AppView::cancelConnectButtonClicked, m_model, &AppModel::cancelConnectToRobot);
	connect(m_view, &AppView::disconnectButtonClicked, m_model, &AppModel::disconnectFromRobot);
	connect(m_view, &AppView::startButtonClicked, m_model, &AppModel::startRobot);
	connect(m_view, &AppView::stopButtonClicked, m_model, &AppModel::stopRobot);

	connect(m_view, &AppView::cartesianMovementPressed, m_model, &AppModel::onCartesianMovementPressed);
	connect(m_view, &AppView::cartesianMovementReleased, m_model, &AppModel::onCartesianMovementReleased);
	connect(m_view, &AppView::articularMovementPressed, m_model, &AppModel::onArticularMovementPressed);
	connect(m_view, &AppView::articularMovementReleased, m_model, &AppModel::onArticularMovementReleased);
	connect(m_view, &AppView::inputToggled, m_model, &AppModel::onInputToggled);
	connect(m_view, &AppView::outputToggled, m_model, &AppModel::onOutputToggled);

	connect(m_view, &AppView::requestNewPose, this, &AppController::onViewRequestNewPose);
	connect(m_view, &AppView::requestNewDelta, this, &AppController::onViewRequestNewDelta);

	// Connexions AppModel -> AppView ou autres
	connect(m_model, &AppModel::robotStatusChanged, m_view, &AppView::onRobotStatusChanged);
	connect(m_model, &AppModel::robotStateChanged, m_view, &AppView::onRobotStateChanged);
	connect(m_model, &AppModel::robotConnected, m_view, &AppView::onRobotConnected);
	connect(m_model, &AppModel::robotDisconnected, m_view, &AppView::onRobotDisconnected);
	connect(m_model, &AppModel::robotStarted, m_view, &AppView::onRobotStarted);
	connect(m_model, &AppModel::robotStopped, m_view, &AppView::onRobotStopped);
	connect(m_model, &AppModel::errorOccurred, this, &AppController::onErrorOccurred);
	connect(m_model, &AppModel::connectionTimeRemainingChanged, m_view, &AppView::onConnectionTimeRemainingChanged);
	connect(m_model, &AppModel::freshRateChanged, m_view, &AppView::onFreshRateChanged);
}

void AppController::removeConnections()
{
	// Connexions AppView -> AppModel  ou autres
	disconnect(m_view, &AppView::connectButtonClicked, m_model, &AppModel::connectToRobot);
	disconnect(m_view, &AppView::cancelConnectButtonClicked, m_model, &AppModel::cancelConnectToRobot);
	disconnect(m_view, &AppView::disconnectButtonClicked, m_model, &AppModel::disconnectFromRobot);
	disconnect(m_view, &AppView::startButtonClicked, m_model, &AppModel::startRobot);
	disconnect(m_view, &AppView::stopButtonClicked, m_model, &AppModel::stopRobot);

	disconnect(m_view, &AppView::cartesianMovementPressed, m_model, &AppModel::onCartesianMovementPressed);
	disconnect(m_view, &AppView::cartesianMovementReleased, m_model, &AppModel::onCartesianMovementReleased);
	disconnect(m_view, &AppView::articularMovementPressed, m_model, &AppModel::onArticularMovementPressed);
	disconnect(m_view, &AppView::articularMovementReleased, m_model, &AppModel::onArticularMovementReleased);
	disconnect(m_view, &AppView::inputToggled, m_model, &AppModel::onInputToggled);
	disconnect(m_view, &AppView::outputToggled, m_model, &AppModel::onOutputToggled);

	disconnect(m_view, &AppView::requestNewPose, this, &AppController::onViewRequestNewPose);
	disconnect(m_view, &AppView::requestNewDelta, this, &AppController::onViewRequestNewDelta);

	// Connexions AppModel -> AppView ou autres
	disconnect(m_model, &AppModel::robotStatusChanged, m_view, &AppView::onRobotStatusChanged);
	disconnect(m_model, &AppModel::robotStateChanged, m_view, &AppView::onRobotStateChanged);
	disconnect(m_model, &AppModel::robotConnected, m_view, &AppView::onRobotConnected);
	disconnect(m_model, &AppModel::robotDisconnected, m_view, &AppView::onRobotDisconnected);
	disconnect(m_model, &AppModel::robotStarted, m_view, &AppView::onRobotStarted);
	disconnect(m_model, &AppModel::robotStopped, m_view, &AppView::onRobotStopped);
	disconnect(m_model, &AppModel::errorOccurred, this, &AppController::onErrorOccurred);
	disconnect(m_model, &AppModel::connectionTimeRemainingChanged, m_view, &AppView::onConnectionTimeRemainingChanged);
	disconnect(m_model, &AppModel::freshRateChanged, m_view, &AppView::onFreshRateChanged);
}

void AppController::onErrorOccurred(const QString& msg)
{
	qWarning() << msg;
}
