#include "CameraModel.h"

CameraModel::CameraModel(CameraReader* reader, QObject* parent) :
    QObject(parent),
    m_cameraReader(reader) 
{
    connect(m_cameraReader, &CameraReader::deviceConnected, this, &CameraModel::deviceConnected);
    connect(m_cameraReader, &CameraReader::deviceDisconnected, this, &CameraModel::deviceDisconnected);
    connect(m_cameraReader, &CameraReader::recordingStarted, this, &CameraModel::recordingStarted);
    connect(m_cameraReader, &CameraReader::recordingStopped, this, &CameraModel::recordingStopped);
    connect(m_cameraReader, &CameraReader::newFrameCaptured, this, &CameraModel::newFrameCaptured);
    connect(m_cameraReader, &CameraReader::errorThrown, this, &CameraModel::errorThrown);
    connect(m_cameraReader, &CameraReader::dimensionsChanged, this, &CameraModel::dimensionsChanged);
    connect(m_cameraReader, &CameraReader::fpsChanged, this, &CameraModel::fpsChanged);
    connect(m_cameraReader, &CameraReader::deviceChanged, this, &CameraModel::deviceChanged);
}

void CameraModel::openCamera()
{
    m_cameraReader->open();
}

void CameraModel::closeCamera() 
{
    m_cameraReader->close();
}

void CameraModel::startRecording(const QString& filename)
{
    m_cameraReader->startRecording(filename);
}

void CameraModel::stopRecording() 
{
    m_cameraReader->stopRecording();
}

void CameraModel::setDevice(int device)
{
    m_cameraReader->setDevice(device);
}
