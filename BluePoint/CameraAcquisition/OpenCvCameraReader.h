#pragma once
#include "CameraReader.h"
#include <QObject>
#include <QString>
#include <QPixmap>
#include <QThread>
#include <QFuture>
#include <QFutureWatcher>

#include "opencv2/opencv.hpp"

class OpenCvCameraReader : public CameraReader
{
	Q_OBJECT

public:
	explicit OpenCvCameraReader(int device = 0, QObject* parent = nullptr);
	~OpenCvCameraReader();

private slots:
	// Inherited via CameraReader
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

	bool m_recording;
};
