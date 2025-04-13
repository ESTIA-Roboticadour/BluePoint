#pragma once
#include "CameraProcessor.h"
#include <QObject>
#include <QString>
#include <QPixmap>
#include <QFuture>
#include <QFutureWatcher>

#include <atomic>
#include <chrono>
#include "opencv2/opencv.hpp"

class WebcamProcessor : public CameraProcessor
{
	Q_OBJECT

public:
	explicit WebcamProcessor(QObject* parent = nullptr);
	~WebcamProcessor();

private slots:
	// Inherited via CameraProcessor
	void open() override;
	void close() override;
	void startRecording(const QString& filename) override;
	void stopRecording() override;

	void captureLoop();
	void captureEnded();

private:
	void getCameraSpecifications();
	bool tryOpenWriter(const QString& filename);
	void releaseCap();
	void releaseWriter();
	void releaseTask();

private:
	cv::VideoCapture* m_cap;
	cv::VideoWriter* m_writer;
	QFuture<void>* m_task;
	QFutureWatcher<void>* m_watcher;

	std::atomic<bool> m_notCreatingWriter;
	std::atomic<bool> m_recording;
	std::chrono::steady_clock::time_point m_startTime;
	float currentFps;
};
