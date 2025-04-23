#include "WebcamProcessor.h"
#include <exception>
#include <QtConcurrent>
#include <QCoreApplication>

WebcamProcessor::WebcamProcessor(QObject* parent) :
	CameraProcessor(parent),
	m_cap(nullptr),
	m_writer(nullptr),
	m_task(nullptr),
	m_watcher(nullptr),
	m_recording(false),
	m_notCreatingWriter(true),
	m_startTime(std::chrono::steady_clock::now()),
	currentFps(0.f)
{
}

WebcamProcessor::~WebcamProcessor()
{
	close();
	if (m_watcher)
	{
		m_watcher->waitForFinished();
	}
	QCoreApplication::processEvents(); // Ensure all events are processed before destruction, as CaptureEnded() may emit signals
}

void WebcamProcessor::getCameraSpecifications()
{
	if (m_cap)
	{
		setWidth(static_cast<int>(m_cap->get(cv::CAP_PROP_FRAME_WIDTH)));
		setHeight(static_cast<int>(m_cap->get(cv::CAP_PROP_FRAME_HEIGHT)));
		setFps(static_cast<float>(m_cap->get(cv::CAP_PROP_FPS)));

		emit dimensionsChanged(getWidth(), getHeight());
		emit fpsChanged(getFps());
	}
}

void WebcamProcessor::releaseCap()
{
	if (m_cap)
	{
		m_cap->release();
		delete m_cap;
		m_cap = nullptr;
	}
}

void WebcamProcessor::releaseWriter()
{
	if (m_writer)
	{
		m_writer->release();
		delete m_writer;
		m_writer = nullptr;
	}
}

void WebcamProcessor::releaseTask()
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

void WebcamProcessor::open()
{
	if (!m_cap)
	{
		m_cap = new cv::VideoCapture();
		if (m_cap->open(0))
		{
			getCameraSpecifications();
			emit deviceConnected();

			m_watcher = new QFutureWatcher<void>();

			QObject::connect(m_watcher, &QFutureWatcher<void>::finished, this, &WebcamProcessor::captureEnded);

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

void WebcamProcessor::close()
{
	stopRecording();
	if (m_watcher && !m_watcher->isCanceled())
		m_watcher->cancel();
}

bool WebcamProcessor::tryOpenWriter(const QString& filename)
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
			releaseWriter();
			emit errorThrown("Writer Error", "Failed to open the writer. " + QString(e.what()));
		}
	}
	return success;
}

void WebcamProcessor::startRecording(const QString& filename)
{
	if (!m_recording.load() && m_notCreatingWriter.load())
	{
		if (m_writer)
		{
			releaseWriter();
		}
		m_notCreatingWriter.store(false);
		if (tryOpenWriter(filename))
		{
			m_recording.store(true);
			m_startTime = std::chrono::steady_clock::now();
			emit recordingStarted(filename);
		}
		else
		{
			emit errorThrown("Recording Error", "Failed to start recording.");
		}
		m_notCreatingWriter.store(true);
	}
}

void WebcamProcessor::stopRecording()
{
	if (m_recording.load())
	{
		m_recording.store(false);
		emit recordingStopped();
	}
}

bool WebcamProcessor::isOpened() const
{
	return m_cap && m_cap->isOpened();
}

void WebcamProcessor::captureLoop()
{
	try
	{
		// to update the recording time
		int recordDuration = 0;
		int newRecordDuration;

		// to update the current fps
		std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::steady_clock::time_point prevTime = now;
		std::chrono::duration<double> delta;
		float currentFps = 0;
		float newCurrentFps = 0;

		cv::Mat frame;
		while (!m_watcher->isCanceled() && m_cap && m_cap->isOpened())
		{
			if (m_cap->read(frame))
			{
				now = std::chrono::high_resolution_clock::now();
				delta = now - prevTime;
				prevTime = now;
				if (delta.count() > 0.0)
					newCurrentFps = 1.0f / static_cast<float>(delta.count());

				if (newCurrentFps != currentFps)
				{
					currentFps = newCurrentFps;
					emit currentFpsChanged(currentFps);
				}

				if (m_watcher->isCanceled())
				{
					break;
				}

				emit newFrameCaptured(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888));

				if (m_recording.load())
				{
					if (m_writer && m_writer->isOpened())
					{
						m_writer->write(frame);
						newRecordDuration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_startTime).count();
						if (newRecordDuration != recordDuration)
						{
							recordDuration = newRecordDuration;
							emit recordingTimeChanged(recordDuration);
						}
					}
					else
					{
						stopRecording();
					}
				}
				else if (m_notCreatingWriter.load() && m_writer)
				{
					releaseWriter();
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
	stopRecording();
	releaseWriter();
}

void WebcamProcessor::captureEnded()
{
	releaseWriter();
	releaseTask();
	releaseCap();
	emit deviceDisconnected();
}
