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

void AppController::onViewRequestRefreshUI(bool isCartesian)
{
	if (isCartesian)
		m_model->getCurrentPose(m_tmpPose);
	else
		m_model->getCurrentJoint(m_tmpPose);
	m_view->updatePose(m_tmpPose);

	m_model->getCurrentDelta(m_tmpPose);
	m_view->updateDelta(m_tmpPose);

	m_model->getCurrentIO(m_tmpInputs, m_tmpOutputs);
	m_view->updateIO(m_tmpInputs, m_tmpOutputs);

	m_model->isJoggingCartesian(m_tmpIsJoggingCartesian);
	m_view->updateJoggingMode(m_tmpIsJoggingCartesian);

	m_model->isMovingInRobotBase(m_tmpIsMovingInRobotBase);
	m_view->updateIsInRobotBase(m_tmpIsMovingInRobotBase);
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
	
	connect(m_view, &AppView::outputClicked, m_model, &AppModel::onOutputClicked);

	connect(m_view, &AppView::joggingCartesianRequest, m_model, &AppModel::onJoggingCartesianRequested);
	connect(m_view, &AppView::joggingArticularRequest, m_model, &AppModel::onJoggingArticularRequested);
	connect(m_view, &AppView::joggingInRobotBaseRequest, m_model, &AppModel::onJoggingInRobotBaseRequested);
	connect(m_view, &AppView::joggingInRobotToolRequest, m_model, &AppModel::onJoggingInRobotToolRequest);

	connect(m_view, &AppView::refreshUiRequest, this, &AppController::onViewRequestRefreshUI, Qt::DirectConnection);

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
	
	disconnect(m_view, &AppView::outputClicked, m_model, &AppModel::onOutputClicked);

	disconnect(m_view, &AppView::joggingCartesianRequest, m_model, &AppModel::onJoggingCartesianRequested);
	disconnect(m_view, &AppView::joggingArticularRequest, m_model, &AppModel::onJoggingArticularRequested);
	disconnect(m_view, &AppView::joggingInRobotBaseRequest, m_model, &AppModel::onJoggingInRobotBaseRequested);
	disconnect(m_view, &AppView::joggingInRobotToolRequest, m_model, &AppModel::onJoggingInRobotToolRequest);

	disconnect(m_view, &AppView::refreshUiRequest, this, &AppController::onViewRequestRefreshUI);

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
