#include "CameraController.h"
#include "WebcamProcessor.h"
#include "BaslerProcessor.h"

CameraController::CameraController(CameraWindow* view, CameraModel* model, QObject* parent) :
	QObject(parent),
	m_view(view),
	m_model(model),
	m_closing(false)
{
	connect(m_view, &CameraWindow::closing, this, &CameraController::onViewClosing);
	connect(m_view, &CameraWindow::openButtonClicked, m_model, &CameraModel::openCamera);
	connect(m_view, &CameraWindow::closeButtonClicked, m_model, &CameraModel::closeCamera);
	connect(m_view, &CameraWindow::startButtonClicked, this, &CameraController::onStartRecordingCamera);
	connect(m_view, &CameraWindow::stopButtonClicked, m_model, &CameraModel::stopRecording);
	connect(m_view, &CameraWindow::deviceChanged, this, &CameraController::setDevice);

	connect(m_model, &CameraModel::deviceConnected, m_view, &CameraWindow::onDeviceConnected);
	connect(m_model, &CameraModel::deviceDisconnected, this, &CameraController::onCameraClosed);
	connect(m_model, &CameraModel::deviceDisconnected, m_view, &CameraWindow::onDeviceDisconnected);
	connect(m_model, &CameraModel::recordingStarted, m_view, &CameraWindow::onRecordingStarted);
	connect(m_model, &CameraModel::recordingStopped, m_view, &CameraWindow::onRecordingStopped);
	connect(m_model, &CameraModel::newFrameCaptured, m_view, &CameraWindow::setFrameLabel);
	connect(m_model, &CameraModel::errorThrown, m_view, &CameraWindow::logError);
	connect(m_model, &CameraModel::dimensionsChanged, this, &CameraController::onDimensionsChanged);
	connect(m_model, &CameraModel::fpsChanged, this, &CameraController::onFpsChanged);
	connect(m_model, &CameraModel::recordingTimeChanged, m_view, &CameraWindow::onRecordingTimeChanged);
	connect(m_model, &CameraModel::currentFpsChanged, this, &CameraController::onCurrentFpsChanged);

	m_model->setWorkDimensions(m_view->getFrameLabelSize());
}

CameraController::~CameraController()
{
	deleteCameraProcessor();
	delete m_model;
	delete m_view;
}

void CameraController::onViewClosing()
{
	m_closing = true;
	m_model->closeCamera();
}

void CameraController::onCameraClosed()
{
	if (m_closing)
	{
		deleteLater();
	}
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

void CameraController::onFpsChanged(float fps)
{
	m_view->setFpsLabel(QString::number(fps));
}

void CameraController::setDevice(int deviceIndex)
{
	QSize size = m_model->getCameraProcessor()->getWorkDimensions();
	deleteCameraProcessor();
	switch (deviceIndex)
	{
	case 0:
		m_model->setCameraProcessor(new WebcamProcessor());
		break;
	case 1:
		m_model->setCameraProcessor(new BaslerProcessor());
		break;
	default:
		break;
	}
	m_model->setWorkDimensions(size);
}

void CameraController::onCurrentFpsChanged(float fps)
{
	m_view->onCurrentFpsChanged(roundf(fps * 100.f) / 100.f);
}

void CameraController::deleteCameraProcessor()
{
	const CameraProcessor* cp = m_model->getCameraProcessor();
	if (cp)
	{
		if (m_model)
			m_model->setCameraProcessor(nullptr);
		delete cp;
	}
}

