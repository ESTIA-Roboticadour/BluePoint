#include "CameraModel.h"

CameraModel::CameraModel(CameraProcessor* cameraProcessor, QObject* parent) :
	QObject(parent),
	m_cameraProcessor(cameraProcessor)
{
	cameraProcessor->setParent(this);
	setupCameraProcessorConnections();
}

void CameraModel::setupCameraProcessorConnections() const
{
	connect(m_cameraProcessor, &CameraProcessor::deviceConnected, this, &CameraModel::deviceConnected);
	connect(m_cameraProcessor, &CameraProcessor::deviceDisconnected, this, &CameraModel::deviceDisconnected);
	connect(m_cameraProcessor, &CameraProcessor::recordingStarted, this, &CameraModel::recordingStarted);
	connect(m_cameraProcessor, &CameraProcessor::recordingStopped, this, &CameraModel::recordingStopped);
	connect(m_cameraProcessor, &CameraProcessor::newFrameCaptured, this, &CameraModel::newFrameCaptured);
	connect(m_cameraProcessor, &CameraProcessor::errorThrown, this, &CameraModel::errorThrown);
	connect(m_cameraProcessor, &CameraProcessor::dimensionsChanged, this, &CameraModel::dimensionsChanged);
	connect(m_cameraProcessor, &CameraProcessor::fpsChanged, this, &CameraModel::fpsChanged);
	connect(m_cameraProcessor, &CameraProcessor::recordingTimeChanged, this, &CameraModel::recordingTimeChanged);
	connect(m_cameraProcessor, &CameraProcessor::currentFpsChanged, this, &CameraModel::currentFpsChanged);
}

void CameraModel::unsetupCameraProcessorConnections() const
{
	disconnect(m_cameraProcessor, &CameraProcessor::deviceConnected, this, &CameraModel::deviceConnected);
	disconnect(m_cameraProcessor, &CameraProcessor::deviceDisconnected, this, &CameraModel::deviceDisconnected);
	disconnect(m_cameraProcessor, &CameraProcessor::recordingStarted, this, &CameraModel::recordingStarted);
	disconnect(m_cameraProcessor, &CameraProcessor::recordingStopped, this, &CameraModel::recordingStopped);
	disconnect(m_cameraProcessor, &CameraProcessor::newFrameCaptured, this, &CameraModel::newFrameCaptured);
	disconnect(m_cameraProcessor, &CameraProcessor::errorThrown, this, &CameraModel::errorThrown);
	disconnect(m_cameraProcessor, &CameraProcessor::dimensionsChanged, this, &CameraModel::dimensionsChanged);
	disconnect(m_cameraProcessor, &CameraProcessor::fpsChanged, this, &CameraModel::fpsChanged);
	disconnect(m_cameraProcessor, &CameraProcessor::recordingTimeChanged, this, &CameraModel::recordingTimeChanged);
	disconnect(m_cameraProcessor, &CameraProcessor::currentFpsChanged, this, &CameraModel::currentFpsChanged);
}

const CameraProcessor* CameraModel::getCameraProcessor() const
{
	return m_cameraProcessor;
}

void CameraModel::setCameraProcessor(CameraProcessor* cameraProcessor)
{
	if (m_cameraProcessor != cameraProcessor) 
	{
		if (m_cameraProcessor) 
		{
			unsetupCameraProcessorConnections();
		}
		m_cameraProcessor = cameraProcessor;
		if (m_cameraProcessor)
		{
			m_cameraProcessor->setParent(this);
			setupCameraProcessorConnections();
		}
	}
}

void CameraModel::openCamera()
{
	m_cameraProcessor->open();
}

void CameraModel::closeCamera() 
{
	m_cameraProcessor->close();
}

void CameraModel::startRecording(const QString& filename)
{
	m_cameraProcessor->startRecording(filename);
}

void CameraModel::stopRecording() 
{
	m_cameraProcessor->stopRecording();
}

void CameraModel::setWorkDimensions(const QSize& size)
{
	m_cameraProcessor->setWorkDimensions(size);
}

bool CameraModel::isCameraOpened() const
{
	return m_cameraProcessor->isOpened();
}
