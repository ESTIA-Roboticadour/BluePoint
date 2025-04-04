#include "OpenCvCameraReader.h"
#include <exception>
#include <QtConcurrent>
#include <QDebug>
#include <QCoreApplication>

OpenCvCameraReader::OpenCvCameraReader(int device, QObject* parent) :
	CameraReader(device, parent),
	m_cap(nullptr),
	m_writer(nullptr),
	m_recording(false),
	m_task(nullptr),
	m_watcher(nullptr)
{
}

OpenCvCameraReader::~OpenCvCameraReader()
{
	close();
}

void OpenCvCameraReader::getCameraSpecifications()
{
	if (m_cap)
	{
		setWidth(static_cast<int>(m_cap->get(cv::CAP_PROP_FRAME_WIDTH)));
		setHeight(static_cast<int>(m_cap->get(cv::CAP_PROP_FRAME_HEIGHT)));
		double fps = m_cap->get(cv::CAP_PROP_FPS);
		setFps(static_cast<int>(fps));

		emit dimensionsChanged(getWidth(), getHeight());
		emit fpsChanged(getFps());
	}
}

void OpenCvCameraReader::releaseCap()
{
	if (m_cap)
	{
		m_cap->release();
		delete m_cap;
		m_cap = nullptr;
	}
}

void OpenCvCameraReader::releaseWriter()
{
	if (m_writer)
	{
		m_writer->release();
		delete m_writer;
		m_writer = nullptr;
	}
}

void OpenCvCameraReader::releaseTask()
{
	if (m_watcher)
	{
		delete m_watcher;
		m_watcher = nullptr;
	}
	if (m_task)
	{
		delete m_task;
		m_task = nullptr;
	}
}

void OpenCvCameraReader::open()
{
	if (!m_cap)
	{
		m_cap = new cv::VideoCapture();
		if (m_cap->open(getDevice()))
		{
			getCameraSpecifications();
			emit deviceConnected();

			m_watcher = new QFutureWatcher<void>();

			QObject::connect(m_watcher, &QFutureWatcher<void>::finished, this, &OpenCvCameraReader::captureEnded);

			m_task = new QFuture<void>(QtConcurrent::run([this]()
				{
					captureLoop();
				}));
			m_watcher->setFuture(*m_task);
		}
		else
		{
			releaseCap();
			emit errorThrown("OpenCV Error", "Failed to open the camera.");
		}
	}
}

void OpenCvCameraReader::close()
{
	if (m_cap)
	{
		stopRecording();
		m_watcher->cancel();
	}
}

bool OpenCvCameraReader::tryOpenWriter(const QString& filename)
{
	bool success = false;
	if (!m_writer)
	{
		m_writer = new cv::VideoWriter();
		try
		{
			m_writer->open(filename.toStdString(),
				cv::VideoWriter::fourcc('X', 'V', 'I', 'D'),
				getFps(),
				cv::Size(getWidth(), getHeight()));
			success = true;
		}
		catch (const std::exception& e)
		{
			emit errorThrown("Writer Error", "Failed to open the writer. " + QString(e.what()));
		}
	}
	return success;
}

void OpenCvCameraReader::startRecording(const QString& filename)
{
	if (!m_writer && tryOpenWriter(filename))
	{
		m_recording = true;
		emit recordingStarted(filename);
	}
	else
	{
		emit errorThrown("Recording Error", "Failed to start recording.");
	}
}

void OpenCvCameraReader::stopRecording()
{
	if (m_recording)
	{
		m_recording = false;
		emit recordingStopped();
	}
}

void OpenCvCameraReader::captureLoop()
{
	try
	{
		cv::Mat frame;
		while (!m_watcher->isCanceled() && m_cap && m_cap->isOpened())
		{
			if (m_cap->read(frame))
			{
				if (m_watcher->isCanceled())
				{
					break;
				}

				QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
				emit newFrameCaptured(QPixmap::fromImage(img));

				if (m_recording)
				{
					if (m_writer && m_writer->isOpened())
					{
						m_writer->write(frame);
					}
					else
					{
						stopRecording();
					}
				}
			}
			else
			{
				emit errorThrown("Capture Error", "Failed to read frame from camera.");
				break;
			}
		}
	}
	catch (const std::exception& e)
	{
		emit errorThrown("Unknown Error", e.what());
	}
	releaseWriter();
}

void OpenCvCameraReader::captureEnded()
{
	releaseWriter();
	releaseTask();
	emit deviceDisconnected();
	releaseCap();
}