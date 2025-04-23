#include "BaslerProcessor.h"
#include "BaslerAPI.h"

#include <exception>
#include <chrono>

#include <QCoreApplication>
#include <QtConcurrent>
#include <QFuture>

#include "pylondataprocessing/PylonDataProcessingIncludes.h"
#include "GenApi/GenApi.h"

BaslerProcessor::BaslerProcessor(QObject* parent) :
	CameraProcessor(parent),
	m_camera(nullptr),
	m_writer(nullptr),
	m_task(nullptr),
	m_watcher(nullptr),
	m_recording(false),
	m_notCreatingWriter(true),
	m_startTime(std::chrono::steady_clock::now()),
	currentFps(0.f)
{
	Pylon::PylonInitialize();
}

BaslerProcessor::~BaslerProcessor()
{
	close();
	if (m_watcher)
	{
		m_watcher->waitForFinished();
		QCoreApplication::processEvents(); // Ensure all events are processed before destruction
	}
	Pylon::PylonTerminate();
}

void BaslerProcessor::configureCamera()
{
	if (!BaslerAPI::maximizeAOI(m_camera))
	{
		emit errorThrown("Basler Configuration Error", "Failed to maximize AOI.");
	}
	if (!BaslerAPI::setPixelFormatBayerRG8(m_camera))
	{
		emit errorThrown("Basler Configuration Error", "Failed to set pixel format.");
	}
	if (!BaslerAPI::setWhiteBalanceOnce(m_camera))
	{
		emit errorThrown("Basler Configuration Error", "Failed to set white balance.");
	}
	if (!BaslerAPI::setFps(m_camera, 30.)) // 30 fps
	{
		emit errorThrown("Basler Configuration Error", "Failed to set frame rate.");
	}
	if (!BaslerAPI::setExposureTime(m_camera, 30000.)) // 30 000 µs (environ 30 fps)
	{
		emit errorThrown("Basler Configuration Error", "Failed to set exposure time.");
	}
}

void BaslerProcessor::getCameraSpecifications()
{
	if (m_camera && m_camera->IsOpen())
	{
		try
		{
			int width;
			int height;
			float fps;

			if (BaslerAPI::getWidth(m_camera, width))
			{
				setWidth(width);
			}
			if (BaslerAPI::getHeight(m_camera, height))
			{
				setHeight(height);
			}
			emit dimensionsChanged(width, height);

			if (BaslerAPI::getFps(m_camera, fps))
			{
				setFps(fps);
				emit fpsChanged(fps);
			}
		}
		catch (const Pylon::GenericException& e)
		{
			emit errorThrown("Basler Error", "Failed to get camera specifications: " + QString::fromStdString(e.GetDescription()));
		}
	}
}

void BaslerProcessor::releaseCamera()
{
	if (m_camera)
	{
		m_camera->StopGrabbing();
		m_camera->Close();
		delete m_camera;
		m_camera = nullptr;
	}
}

void BaslerProcessor::releaseWriter()
{
	if (m_writer)
	{
		m_writer->release();
		delete m_writer;
		m_writer = nullptr;
	}
}

void BaslerProcessor::releaseTask()
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

void BaslerProcessor::open()
{
	try
	{
		m_camera = new Pylon::CInstantCamera(Pylon::CTlFactory::GetInstance().CreateFirstDevice());
		if (m_camera)
		{
			m_camera->Open();
			if (m_camera->IsOpen())
			{
				configureCamera();
				getCameraSpecifications();
				if (getWorkWidth() == 0 || getWorkHeight() == 0)
				{
					setWorkDimensions(getWidth(), getHeight());
				}
				emit deviceConnected();

				// start the capture loop
				m_camera->StartGrabbing();
				if (m_camera->IsGrabbing())
				{
					m_watcher = new QFutureWatcher<void>();
					connect(m_watcher, &QFutureWatcher<void>::finished, this, &BaslerProcessor::captureEnded);

					m_task = new QFuture<void>(QtConcurrent::run([this]() {
						captureLoop();
						}));
					m_watcher->setFuture(*m_task);
				}
				else
				{
					emit errorThrown("Basler Error", "Can not start grabbing frame");
				}

				if (!m_task)
				{
					releaseCamera();
				}
			}
			else
			{
				emit errorThrown("Basler Error", "Can not open the camera");
			}
		}
		else
		{
			emit errorThrown("Basler Error", "No camera found");
		}
	}
	catch (const Pylon::GenericException& e)
	{
		emit errorThrown("Basler Error", e.GetDescription());
	}
}

void BaslerProcessor::close()
{
	stopRecording();
	if (m_watcher && !m_watcher->isCanceled())
		m_watcher->cancel();
}

bool BaslerProcessor::tryOpenWriter(const QString& filename)
{
	bool success = false;
	if (!m_writer)
	{
		m_writer = new cv::VideoWriter();
		try
		{
			m_writer->open(filename.toStdString(),
				cv::VideoWriter::fourcc('X', 'V', 'I', 'D'),
				getFps(), //30., // 
				cv::Size(getWorkWidth(), getWorkHeight()));
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

void BaslerProcessor::startRecording(const QString& filename)
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
			m_startTime = std::chrono::high_resolution_clock::now();
			emit recordingStarted(filename);
		}
		else
		{
			emit errorThrown("Recording Error", "Failed to start recording.");
		}
		m_notCreatingWriter.store(true);
	}
}

void BaslerProcessor::stopRecording()
{
	if (m_recording.load())
	{
		m_recording.store(false);
		emit recordingStopped();
	}
}

bool BaslerProcessor::isOpened() const
{
	return m_camera && m_camera->IsOpen();
}

//void BaslerProcessor::captureLoop() // version debug pour comparer les performances
//{
//	try
//	{
//		Pylon::CGrabResultPtr ptrGrabResult;
//		Pylon::CImageFormatConverter converter;
//		converter.OutputPixelFormat = Pylon::PixelType_BGR8packed;
//
//		Pylon::CPylonImage image;
//
//		// pour le debug
//		std::chrono::steady_clock::time_point start;
//		std::chrono::steady_clock::time_point end;
//		double durationMs = 0;
//		std::chrono::steady_clock::time_point start2;
//		std::chrono::steady_clock::time_point end2;
//		double durationMs2 = 0;
//		std::chrono::steady_clock::time_point start3;
//		std::chrono::steady_clock::time_point end3;
//		double durationMs3 = 0;
//		std::chrono::steady_clock::time_point start4;
//		std::chrono::steady_clock::time_point end4;
//		double durationMs4 = 0;
//		// fin - pour le debug
//
//		int workWidth = getWorkWidth();
//		int workHeight = getWorkHeight();
//		int frameWidth = getWidth();
//		int frameHeight = getHeight();
//		int newWidth = 0;
//		int newHeight = 0;
//		int count = 0;
//
//		bool hasToResize = workWidth != frameWidth || workHeight != frameHeight;
//		findNewSizeToKeepAspectRatio(frameWidth, frameHeight, newWidth, newHeight);
//
//		cv::Size newSize(newWidth, newHeight);		// 574x480 (issue de 2448x2048)
//		cv::Size workSize(workWidth, workHeight);	// 640x480
//
//		cv::Mat frame;
//		cv::Mat workFrame = cv::Mat::zeros(workSize, CV_8UC3);
//		cv::Mat resizedFrame = cv::Mat::zeros(newSize, CV_8UC3);
//
//		QImage outImage(workSize.width, workSize.height, QImage::Format_RGB888);
//		outImage.fill(Qt::black); // Initialiser l'image avec du noir
//
//		while (!m_watcher->isCanceled() && m_camera && m_camera->IsGrabbing())
//		{
//			m_camera->RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
//
//			if (ptrGrabResult->GrabSucceeded())
//			{
//				// avant : conversion RG8 en BGR8, puis conversion vers OpenCV puis redimensionnement, puis centrage, puis conversion vers QImage
//				start = std::chrono::high_resolution_clock::now();
//				if (hasToResize)
//				{
//					// Convertir la frame de BayerRG8 en RGB8
//					converter.Convert(image, ptrGrabResult);
//					// Conversion OpenCV
//					frame = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)image.GetBuffer());
//					// Redimensionnement
//					cv::resize(frame, resizedFrame, newSize); // resize the frame with the best dimensions and keep the aspect ratio
//					//Centrage
//					int offsetX = (workWidth - resizedFrame.cols) / 2;
//					int offsetY = (workHeight - resizedFrame.rows) / 2;
//					cv::Rect roi(offsetX, offsetY, resizedFrame.cols, resizedFrame.rows);
//					resizedFrame.copyTo(workFrame(roi)); // center the resizedFrame into the workFrame
//				}
//				else
//				{
//					converter.Convert(image, ptrGrabResult);
//					workFrame = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)image.GetBuffer());
//				}
//				// OpenCV vers QImage
//				outImage = QImage(workFrame.data, workFrame.cols, workFrame.rows, workFrame.step, QImage::Format_BGR888);
//				end = std::chrono::high_resolution_clock::now();
//				durationMs = (std::chrono::duration<double>(end - start).count() * 1000.0);
//
//				// version 1 : conversion, redimensionnement et centrage vers OpenCV et QImage
//				start2 = std::chrono::high_resolution_clock::now();
//				//convertAndResize1(ptrGrabResult, workFrame, outImage, newWidth, newHeight);
//				end2 = std::chrono::high_resolution_clock::now();
//				durationMs2 = (std::chrono::duration<double>(end2 - start2).count() * 1000.0);
//
//				// version Optimisé : conversion, redimensionnement et centrage vers OpenCV et QImage
//				start3 = std::chrono::high_resolution_clock::now();
//				//convertAndResize2(ptrGrabResult, workFrame, outImage, newWidth, newHeight);
//				end3 = std::chrono::high_resolution_clock::now();
//				durationMs3 = (std::chrono::duration<double>(end3 - start3).count() * 1000.0);
//
//				// version Optimisé Multi thread : conversion, redimensionnement et centrage vers OpenCV et QImage
//				start4 = std::chrono::high_resolution_clock::now();
//				convertAndResize3(ptrGrabResult, workFrame, outImage, newWidth, newHeight);
//				end4 = std::chrono::high_resolution_clock::now();
//				durationMs4 = (std::chrono::duration<double>(end4 - start4).count() * 1000.0);
//
//				qDebug() << durationMs << ';' << durationMs2 << ';' << durationMs3 << ';' << durationMs4;
//
//				emit newFrameCaptured(outImage);
//
//				if (m_recording.load() && m_writer && m_writer->isOpened())
//				{
//					m_writer->write(workFrame);
//				}
//				else if (m_notCreatingWriter.load() && m_writer)
//				{
//					releaseWriter();
//				}
//			}
//			else
//			{
//				emit errorThrown("Capture Error", "Grab failed.");
//			}
//		}
//		m_camera->StopGrabbing();
//	}
//	catch (const Pylon::GenericException& e)
//	{
//		emit errorThrown("Basler Error", e.GetDescription());
//	}
//
//	stopRecording();
//	releaseWriter();
//}

void BaslerProcessor::captureLoop()
{
	try
	{
		// to update the recording time
		std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		int recordDuration = 0;
		int newRecordDuration;

		// to update the current fps
		int currentFps = 0;
		int newCurrentFps;

		Pylon::CGrabResultPtr ptrGrabResult;

		int workWidth = getWorkWidth();
		int workHeight = getWorkHeight();
		int frameWidth = getWidth();
		int frameHeight = getHeight();
		int newWidth = 0;
		int newHeight = 0;
		int count = 0;

		findNewSizeToKeepAspectRatio(frameWidth, frameHeight, newWidth, newHeight);

		cv::Size workSize(workWidth, workHeight);	// 640x480
		cv::Mat workFrame = cv::Mat::zeros(workSize, CV_8UC3);

		QImage outImage(workSize.width, workSize.height, QImage::Format_RGB888);
		outImage.fill(Qt::black); // Initialiser l'image avec du noir

		while (!m_watcher->isCanceled() && m_camera && m_camera->IsGrabbing())
		{
			m_camera->RetrieveResult(5000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);

			newCurrentFps = 1.f / std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - currentTime).count();
			currentTime = std::chrono::high_resolution_clock::now();
			if (newCurrentFps != currentFps)
			{
				currentFps = newCurrentFps;
				emit currentFpsChanged(currentFps);
			}

			if (ptrGrabResult->GrabSucceeded())
			{
				// version Optimisé Multi thread
				convertAndResize3(ptrGrabResult, workFrame, outImage, newWidth, newHeight);

				emit newFrameCaptured(outImage);

				if (m_recording.load() && m_writer && m_writer->isOpened())
				{
					m_writer->write(workFrame);

					newRecordDuration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_startTime).count();
					if (newRecordDuration != recordDuration)
					{
						recordDuration = newRecordDuration;
						emit recordingTimeChanged(recordDuration);
					}

				}
				else if (m_notCreatingWriter.load() && m_writer)
				{
					releaseWriter();
				}
			}
			else
			{
				emit errorThrown("Capture Error", "Grab failed.");
			}
		}
		m_camera->StopGrabbing();
	}
	catch (const Pylon::GenericException& e)
	{
		emit errorThrown("Basler Error", e.GetDescription());
	}

	stopRecording();
	releaseWriter();
}

void BaslerProcessor::captureEnded()
{
	releaseWriter();
	releaseTask();
	releaseCamera();
	emit deviceDisconnected();
}

// Fonction pour estimer B, G, R à partir du Bayer
//void BaslerProcessor::demosaicPixel1(const uint8_t* bayer, int x, int y, int width, int height, int stride, uint8_t& B, uint8_t& G, uint8_t& R)
//{
//	int index = y * stride + x;
//	uint8_t center = bayer[index];
//
//	// Pour éviter les débordements
//	int x_m1 = std::max(x - 1, 0);
//	int x_p1 = std::min(x + 1, width - 1);
//	int y_m1 = std::max(y - 1, 0);
//	int y_p1 = std::min(y + 1, height - 1);
//
//	int idx_m1x = y * stride + x_m1;
//	int idx_p1x = y * stride + x_p1;
//	int idx_ym1 = y_m1 * stride + x;
//	int idx_yp1 = y_p1 * stride + x;
//
//	if ((y % 2) == 0) {
//		if ((x % 2) == 0) {
//			// R position
//			R = center;
//			G = (bayer[idx_m1x] + bayer[idx_p1x] + bayer[idx_ym1] + bayer[idx_yp1]) / 4;
//			B = (bayer[y_m1 * stride + x_m1] + bayer[y_m1 * stride + x_p1] +
//				bayer[y_p1 * stride + x_m1] + bayer[y_p1 * stride + x_p1]) / 4;
//		}
//		else {
//			// G position (even row, odd col)
//			G = center;
//			R = (bayer[y * stride + x_m1] + bayer[y * stride + x_p1]) / 2;
//			B = (bayer[y_m1 * stride + x] + bayer[y_p1 * stride + x]) / 2;
//		}
//	}
//	else {
//		if ((x % 2) == 0) {
//			// G position (odd row, even col)
//			G = center;
//			R = (bayer[y_m1 * stride + x] + bayer[y_p1 * stride + x]) / 2;
//			B = (bayer[y * stride + x_m1] + bayer[y * stride + x_p1]) / 2;
//		}
//		else {
//			// B position
//			B = center;
//			G = (bayer[idx_m1x] + bayer[idx_p1x] + bayer[idx_ym1] + bayer[idx_yp1]) / 4;
//			R = (bayer[y_m1 * stride + x_m1] + bayer[y_m1 * stride + x_p1] +
//				bayer[y_p1 * stride + x_m1] + bayer[y_p1 * stride + x_p1]) / 4;
//		}
//	}
//}

//void BaslerProcessor::convertAndResize1(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight)
//{
//	const int srcWidth = ptrGrabResult->GetWidth();
//	const int srcHeight = ptrGrabResult->GetHeight();
//	const int stride = ptrGrabResult->GetPaddingX() + srcWidth;
//
//	const uint8_t* srcBuffer = static_cast<uint8_t*>(ptrGrabResult->GetBuffer());
//
//	const int dstWidth = outFrame.cols;
//	const int dstHeight = outFrame.rows;
//	const int offsetX = (dstWidth - newWidth) / 2;
//	const int offsetY = (dstHeight - newHeight) / 2;
//
//
//	for (int dstY = 0; dstY < newHeight; ++dstY) {
//		int srcY = dstY * srcHeight / newHeight;
//		cv::Vec3b* outRow = outFrame.ptr<cv::Vec3b>(dstY + offsetY);
//		uint8_t* imgRow = outImage.scanLine(dstY + offsetY);
//
//		for (int dstX = 0; dstX < newWidth; ++dstX) {
//			int srcX = dstX * srcWidth / newWidth;
//
//			uint8_t B, G, R;
//			demosaicPixel1(srcBuffer, srcX, srcY, srcWidth, srcHeight, stride, B, G, R);
//
//			// Écriture OpenCV
//			cv::Vec3b& pixel = outFrame.at<cv::Vec3b>(dstY + offsetY, dstX + offsetX);
//			pixel[0] = B;
//			pixel[1] = G;
//			pixel[2] = R;
//
//			// Écriture QImage (format RGB888 → ordre: R, G, B)
//			uint8_t* qPixel = &imgRow[(dstX + offsetX) * 3];
//			qPixel[0] = R;
//			qPixel[1] = G;
//			qPixel[2] = B;
//		}
//	}
//}

// Fonction pour estimer B, G, R à partir du Bayer
void BaslerProcessor::demosaicPixel2(const uint8_t* bayer, int& x, int& y, const int& width, const int& height, const int& stride, bool& rowEven, bool& colEven, uint8_t& B, uint8_t& G, uint8_t& R)
{
	int index = y * stride + x;
	uint8_t center = bayer[index];

	// Pour éviter les débordements
	int x_m1 = x > 0 ? x - 1 : 0;
	int x_p1 = x < width - 1 ? x + 1 : width - 1;
	int y_m1 = y > 0 ? y - 1 : 0;
	int y_p1 = y < height - 1 ? y + 1 : height - 1;

	int idx_m1x = y * stride + x_m1;
	int idx_p1x = y * stride + x_p1;
	int idx_ym1 = y_m1 * stride + x;
	int idx_yp1 = y_p1 * stride + x;

	if (rowEven) {
		if (colEven) {
			int y_m1_stride = y_m1 * stride;
			int y_p1_stride = y_p1 * stride;
			// R position
			R = center;
			G = (bayer[idx_m1x] + bayer[idx_p1x] + bayer[idx_ym1] + bayer[idx_yp1]) / 4;
			B = (bayer[y_m1_stride + x_m1] + bayer[y_m1_stride + x_p1] +
				bayer[y_p1_stride + x_m1] + bayer[y_p1_stride + x_p1]) / 4;
		}
		else {
			// G position (even row, odd col)
			G = center;
			R = (bayer[idx_m1x] + bayer[idx_p1x]) / 2;
			B = (bayer[idx_ym1] + bayer[idx_yp1]) / 2;
		}
	}
	else {
		if (colEven) {
			// G position (odd row, even col)
			G = center;
			R = (bayer[idx_ym1] + bayer[idx_yp1]) / 2;
			B = (bayer[idx_m1x] + bayer[idx_p1x]) / 2;
		}
		else {
			int y_m1_stride = y_m1 * stride;
			int y_p1_stride = y_p1 * stride;
			// B position
			B = center;
			G = (bayer[idx_m1x] + bayer[idx_p1x] + bayer[idx_ym1] + bayer[idx_yp1]) / 4;
			R = (bayer[y_m1_stride + x_m1] + bayer[y_m1_stride + x_p1] +
				bayer[y_p1_stride + x_m1] + bayer[y_p1_stride + x_p1]) / 4;
		}
	}
}

//void BaslerProcessor::convertAndResize2(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight)
//{
//	const int srcWidth = ptrGrabResult->GetWidth();
//	const int srcHeight = ptrGrabResult->GetHeight();
//	const int stride = ptrGrabResult->GetPaddingX() + srcWidth;
//
//	const uint8_t* srcBuffer = static_cast<uint8_t*>(ptrGrabResult->GetBuffer());
//
//	const int dstWidth = outFrame.cols;
//	const int dstHeight = outFrame.rows;
//	const int offsetX = (dstWidth - newWidth) / 2;
//	const int offsetY = (dstHeight - newHeight) / 2;
//
//	int dstY;
//	int srcY;
//	int dstX;
//	int srcX;
//	uint8_t B, G, R;
//
//	bool rowEven;
//	bool colEven;
//
//	cv::Vec3b* outRow;
//	uint8_t* imgRow;
//	uint8_t* qPixel;
//
//	for (dstY = 0; dstY < newHeight; ++dstY)
//	{
//		srcY = dstY * srcHeight / newHeight;
//		rowEven = (srcY % 2) == 0;
//		outRow = outFrame.ptr<cv::Vec3b>(dstY + offsetY);
//		imgRow = outImage.scanLine(dstY + offsetY);
//
//		for (dstX = 0; dstX < newWidth; ++dstX)
//		{
//			srcX = dstX * srcWidth / newWidth;
//			colEven = (srcX % 2) == 0;
//
//			demosaicPixel2(srcBuffer, srcX, srcY, srcWidth, srcHeight, stride, rowEven, colEven, B, G, R);
//
//			// Écriture OpenCV
//			//cv::Vec3b& pixel = outFrame.at<cv::Vec3b>(dstY + offsetY, dstX + offsetX);
//			cv::Vec3b& pixel = outRow[dstX + offsetX];
//			pixel[0] = B;
//			pixel[1] = G;
//			pixel[2] = R;
//
//			// Écriture QImage (format RGB888 → ordre: R, G, B)
//			qPixel = &imgRow[(dstX + offsetX) * 3];
//			qPixel[0] = R;
//			qPixel[1] = G;
//			qPixel[2] = B;
//
//			colEven = !colEven;
//		}
//		rowEven = !rowEven;
//	}
//}

void BaslerProcessor::convertAndResize3(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight)
{
	int xMid = newWidth / 2;
	int yMid = newHeight / 2;

	auto task1 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResize3Task(ptrGrabResult, outFrame, outImage, newWidth, newHeight, 0, xMid, 0, yMid);
		});

	auto task2 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResize3Task(ptrGrabResult, outFrame, outImage, newWidth, newHeight, xMid, newWidth, 0, yMid);
		});

	auto task3 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResize3Task(ptrGrabResult, outFrame, outImage, newWidth, newHeight, 0, xMid, yMid, newHeight);
		});

	auto task4 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResize3Task(ptrGrabResult, outFrame, outImage, newWidth, newHeight, xMid, newWidth, yMid, newHeight);
		});

	// Attendre que tout soit terminé
	task1.waitForFinished();
	task2.waitForFinished();
	task3.waitForFinished();
	task4.waitForFinished();
}

void BaslerProcessor::convertAndResize3Task(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int& newWidth, int& newHeight, int xStart, int xEnd, int yStart, int yEnd)
{
	const int srcWidth = ptrGrabResult->GetWidth();
	const int srcHeight = ptrGrabResult->GetHeight();
	const int stride = ptrGrabResult->GetPaddingX() + srcWidth;

	const uint8_t* srcBuffer = static_cast<uint8_t*>(ptrGrabResult->GetBuffer());

	const int dstWidth = outFrame.cols;
	const int dstHeight = outFrame.rows;
	const int offsetX = (dstWidth - newWidth) / 2;
	const int offsetY = (dstHeight - newHeight) / 2;

	int dstY;
	int srcY;
	int dstX;
	int srcX;
	uint8_t B, G, R;

	bool rowEven;
	bool colEven;
	cv::Vec3b* outRow;
	uint8_t* imgRow;
	uint8_t* qPixel;

	for (dstY = yStart; dstY < yEnd; ++dstY)
	{
		srcY = dstY * srcHeight / newHeight;
		rowEven = (srcY % 2) == 0;
		outRow = outFrame.ptr<cv::Vec3b>(dstY + offsetY);
		imgRow = outImage.scanLine(dstY + offsetY);

		for (dstX = xStart; dstX < xEnd; ++dstX)
		{
			srcX = dstX * srcWidth / newWidth;
			colEven = (srcX % 2) == 0;

			demosaicPixel2(srcBuffer, srcX, srcY, srcWidth, srcHeight, stride, rowEven, colEven, B, G, R);

			// Écriture OpenCV
			//cv::Vec3b& pixel = outFrame.at<cv::Vec3b>(dstY + offsetY, dstX + offsetX);
			cv::Vec3b& pixel = outRow[dstX + offsetX];
			pixel[0] = B;
			pixel[1] = G;
			pixel[2] = R;

			// Écriture QImage (format RGB888 → ordre: R, G, B)
			qPixel = &imgRow[(dstX + offsetX) * 3];
			qPixel[0] = R;
			qPixel[1] = G;
			qPixel[2] = B;
		}
	}
}
