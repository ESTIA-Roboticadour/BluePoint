#include "CameraController.h"

CameraController::CameraController(CameraWindow* view, CameraModel* model, QObject* parent) :
	QObject(parent),
	m_view(view),
	m_model(model)
{
	connect(m_view, &CameraWindow::closing, this, &CameraController::onViewClosing);
	connect(m_view, &CameraWindow::openButtonClicked, m_model, &CameraModel::openCamera);
	connect(m_view, &CameraWindow::closeButtonClicked, m_model, &CameraModel::closeCamera);
	connect(m_view, &CameraWindow::startButtonClicked, this, &CameraController::onStartRecordingCamera);
	connect(m_view, &CameraWindow::stopButtonClicked, m_model, &CameraModel::stopRecording);
	connect(m_view, &CameraWindow::deviceChanged, m_model, &CameraModel::setDevice);

	connect(m_model, &CameraModel::deviceConnected, m_view, &CameraWindow::onDeviceConnected);
	connect(m_model, &CameraModel::deviceDisconnected, m_view, &CameraWindow::onDeviceDisconnected);
	connect(m_model, &CameraModel::recordingStarted, m_view, &CameraWindow::onRecordingStarted);
	connect(m_model, &CameraModel::recordingStopped, m_view, &CameraWindow::onRecordingStopped);
	connect(m_model, &CameraModel::newFrameCaptured, m_view, &CameraWindow::setFrameLabel);
	connect(m_model, &CameraModel::errorThrown, m_view, &CameraWindow::logError);
	connect(m_model, &CameraModel::dimensionsChanged, this, &CameraController::onDimensionsChanged);
	connect(m_model, &CameraModel::fpsChanged, this, &CameraController::onFpsChanged);
	connect(m_model, &CameraModel::deviceChanged, m_view, &CameraWindow::deviceChanged);
}

CameraController::~CameraController()
{
	delete m_view;
	delete m_model;
}

void CameraController::onViewClosing()
{
	m_model->closeCamera();
	deleteLater();
}

void CameraController::onStartRecordingCamera()
{
	QString filename = m_view->getVideoFilename();
	if (!filename.isEmpty()) 
	{
		m_model->startRecording(filename);
	}
}

void CameraController::onDimensionsChanged(int width, int height)
{
	m_view->setDimensionsLabel(QString::number(width) + "x" + QString::number(height));
}

void CameraController::onFpsChanged(int fps)
{
	m_view->setFpsLabel(QString::number(fps));
}
