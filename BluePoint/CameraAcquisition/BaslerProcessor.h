#pragma once

#include "CameraProcessor.h"

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QFuture>
#include <QFutureWatcher>

#include <atomic>
#include "pylon/PylonIncludes.h"
#include "opencv2/opencv.hpp"

class BaslerProcessor : public CameraProcessor
{
	Q_OBJECT

public:
	explicit BaslerProcessor(QObject* parent = nullptr);
	~BaslerProcessor();

private slots:
	// Inherited via CameraProcessor
	void open() override;
	void close() override;
	void startRecording(const QString& filename) override;
	void stopRecording() override;

	void captureLoop();
	void captureEnded();

private:
	
	void configureCamera();
	void getCameraSpecifications();
	bool tryOpenWriter(const QString& filename);
	void releaseCamera();
	void releaseWriter();
	void releaseTask();

	//void convertAndResizeGPT(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight);
	//void demosaicPixelGPT(const uint8_t* bayer, int x, int y, int width, int height, int stride, uint8_t& B, uint8_t& G, uint8_t& R);

	//void convertAndResize2(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight);
	void demosaicPixel2(const uint8_t* bayer, int& x, int& y, const int& width, const int& height, const int& stride, bool& rowEven, bool& colEven, uint8_t& B, uint8_t& G, uint8_t& R);

	void convertAndResize3(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight);
	void convertAndResize3Task(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int& newWidth, int& newHeight, int xStart, int xEnd, int yStart, int yEnd);

private:
	Pylon::CInstantCamera* m_camera;
	cv::VideoWriter* m_writer;
	QFuture<void>* m_task;
	QFutureWatcher<void>* m_watcher;

	std::atomic<bool> m_notCreatingWriter;
	std::atomic<bool> m_recording;
};
