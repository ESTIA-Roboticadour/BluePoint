#include "BaslerCamera2.h"

#include <QCoreApplication>
#include <QtConcurrent>
#include <QImage>
#include <QString>

#include <pylon/PylonUtilityIncludes.h>   // CPylonImage, CImageFormatConverter
#include <GenApi/GenApi.h>                // NodeMap helpers

#include <opencv2/imgproc.hpp>

#include <thread>
#include <chrono>

//------------- init static --------------------------------------------------
std::atomic_int BaslerCamera2::s_pylonUsers{ 0 };

//------------- ctor / dtor --------------------------------------------------
BaslerCamera2::BaslerCamera2(QObject* parent) :
	Camera(parent),
	m_task(nullptr),
	m_watcher(nullptr),
	m_isReleased(false),
	m_isReleasing(false)
{
	pylonInit();
}

BaslerCamera2::~BaslerCamera2()
{
	if (!m_isReleased)
	{
		release();
	}
	pylonTerminate();
}

void BaslerCamera2::release()
{
	if (m_isReleasing)
		return;

	m_isReleasing = true;
	if (isOpened())
	{
		close();
		if (m_watcher)
		{
			m_watcher->waitForFinished();
			QCoreApplication::processEvents(); // Ensure all events are processed before destruction
		}
		while (m_watcher)
			QCoreApplication::processEvents();
	}
	if (isConnected())
		disconnect();
	m_isReleasing = false;
	m_isReleased = true;
}

void BaslerCamera2::setConfig(const CameraConfig* cfg)
{
	if (auto* baslerCfg = dynamic_cast<const BaslerCameraConfig*>(cfg))
	{
		setConfig(baslerCfg);
	}
	else
	{
		qWarning() << "[BaslerCamera] Invalid config type, expected BaslerCamera2Config";
	}
}

//------------- config -------------------------------------------------------
void BaslerCamera2::setConfig(const BaslerCameraConfig* cfg)
{
	m_config = cfg;
	if (isOpened())
		applyConfig();
}

//------------- status -------------------------------------------------------
bool BaslerCamera2::isConnected() const { return m_camera && m_camera->IsPylonDeviceAttached(); }
bool BaslerCamera2::isOpened()   const { return m_camera && m_camera->IsOpen(); }

//------------- connect / disconnect ----------------------------------------
void BaslerCamera2::connect()
{
	if (isConnected())
		return;

	try
	{
		m_camera = std::make_unique<Pylon::CInstantCamera>(Pylon::CTlFactory::GetInstance().CreateFirstDevice());
		emit connected();
	}
	catch (const Pylon::GenericException& e)
	{
		emit failedToConnect(tr("[BaslerCamera2] Failed to connect:") + e.GetDescription());
		m_camera.reset();
	}
}

void BaslerCamera2::disconnect()
{
	if (!isConnected())
		return;

	try
	{
		close();
		m_camera->DetachDevice();
		m_camera.reset();
		emit disconnected();
	}
	catch (const Pylon::GenericException& e)
	{
		emit failedToDisconnect(tr("[BaslerCamera2] Failed to disconnect:") + e.GetDescription());
	}
}

//------------- open / close -------------------------------------------------
void BaslerCamera2::open(const CameraConfig* cfg)
{
	if (!isConnected())
	{
		emit failedToOpen("[BaslerCamera2] Failed to open: Camera not connected");
		return;
	}
	if (!isOpened())
	{
		try
		{
			try
			{
				m_camera->Open();
			}
			catch (const Pylon::GenericException& e)
			{
				emit failedToOpen(tr("[BaslerCamera2] Failed to open: ") + e.GetDescription());
				return;
			}

			if (m_camera->IsOpen())
			{
				if (cfg)
				{
					try
					{
						setConfig(cfg);
					}
					catch (const Pylon::GenericException& e)
					{
						emit failedToOpen(tr("[BaslerCamera2] Invalid configuration: ") + e.GetDescription());
						close();
						return;
					}
				}
				startGrabbing();
				if (isGrabbing() && m_watcher)
				{
					emit opened();
				}
				else
				{
					emit failedToOpen("[BaslerCamera2] Failed to start grabbing");
					close();
				}
			}
			else
			{
				emit failedToOpen("[BaslerCamera2] Failed to close");
			}
		}
		catch (const Pylon::GenericException& e)
		{
			emit failedToOpen(QString::fromLatin1(e.GetDescription()));
			if (isOpened())
				close();
		}
	}
}

void BaslerCamera2::close()
{
	if (!isOpened())
		return;

	try
	{
		if (m_watcher && !m_watcher->isCanceled())
		{
			m_watcher->cancel();
		}
		else
		{
			m_camera->Close();
			emit closed();
		}
	}
	catch (const Pylon::GenericException& e)
	{
		emit failedToClose(tr("[BaslerCamera2] Failed to close: ") + e.GetDescription());
	}
}

//------------- grabbing -----------------------------------------------------
void BaslerCamera2::startGrabbing()
{
	if (!isOpened())
		return;

	if (isGrabbing() || m_watcher)
		return;

	m_camera->MaxNumBuffer = 10;
	m_camera->StartGrabbing(Pylon::GrabStrategy_LatestImageOnly, Pylon::GrabLoop_ProvidedByUser);

	if (m_camera->IsGrabbing())
	{
		m_watcher = new QFutureWatcher<void>();
		QObject::connect(m_watcher, &QFutureWatcher<void>::finished, this, &BaslerCamera2::grabEnded);

		m_task = new QFuture<void>(QtConcurrent::run([this]() { grabLoop(); }));
		m_watcher->setFuture(*m_task);
	}

//	std::thread([this]
//		{
//			Pylon::CGrabResultPtr        ptr;
//			Pylon::CImageFormatConverter conv;
//			conv.OutputPixelFormat = Pylon::PixelType_BGR8packed;
//			Pylon::CPylonImage           pyImg;
//			cv::Mat                      matRGB;
//
//#ifdef _DEBUG
//			std::chrono::steady_clock::time_point start;
//			std::chrono::steady_clock::time_point end;
//			double deltaMs;
//			int displayCounter = 0;
//#endif // _DEBUG
//
//			while (m_camera && m_camera->IsGrabbing())
//			{
//				try
//				{
//#ifdef _DEBUG
//					start = std::chrono::steady_clock::now();
//#endif // _DEBUG
//					m_camera->RetrieveResult(2000, ptr, Pylon::TimeoutHandling_ThrowException);
//					if (!ptr->GrabSucceeded())
//					{
//						emit errorThrown("[BaslerCamera2] Grab error", ptr->GetErrorDescription().c_str());
//						continue;
//					}
//
//					// BGR header sur buffer Pylon
//					conv.Convert(pyImg, ptr);
//
//					cv::Mat matBGR(ptr->GetHeight(), ptr->GetWidth(), CV_8UC3,
//						const_cast<std::uint8_t*>(
//							static_cast<const std::uint8_t*>(pyImg.GetBuffer())),
//						ptr->GetWidth() * 3);
//
//					// BGR -> RGB (tampon ré-utilisable)
//					matRGB.create(matBGR.rows, matBGR.cols, CV_8UC3);
//					cv::cvtColor(matBGR, matRGB, cv::COLOR_BGR2RGB);
//
//					// sauvegarde thread-safe
//					{
//						std::scoped_lock lk(m_frameMtx);
//						matRGB.copyTo(m_lastFrame);
//					}
//
//					// QImage
//					QImage image(matRGB.data, matRGB.cols, matRGB.rows, static_cast<int>(matRGB.step), QImage::Format_RGB888);
//
//#ifdef _DEBUG
//					end = std::chrono::steady_clock::now();
//					deltaMs = std::chrono::duration<double, std::milli>(end - start).count();
//					displayCounter++;
//					if (displayCounter == 15)
//					{
//						qDebug() << deltaMs;
//						displayCounter = 0;
//					}
//#endif // _DEBUG
//
//					emit imageProvided(image.copy());   // deep-copy -> sûr pour Qt
//
//					// si besoin d'un signal OpenCV :
//					emit cvFrameReady();
//
//				}
//				catch (const Pylon::GenericException& e)
//				{
//					emit errorThrown("[BaslerCamera2] Grab error", e.GetDescription());
//					continue;
//				}
//			}
//		}).detach();
}

void BaslerCamera2::stopGrabbing()
{
	if (isGrabbing())
		m_camera->StopGrabbing();
}

void BaslerCamera2::grabLoop()
{
	Pylon::CGrabResultPtr ptrGrabResult;

	cv::Size size(m_config->getWidth(), m_config->getHeight());
	cv::Mat frame = cv::Mat::zeros(size, CV_8UC3);
	QImage outImage = QImage(m_config->getWidth(), m_config->getHeight(), QImage::Format_RGB888);
	outImage.fill(Qt::black);

#ifdef _DEBUG
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	double deltaMs;
	int displayCounter = 0;
#endif // _DEBUG

	try
	{
		while (!m_watcher->isCanceled() && m_camera && m_camera->IsGrabbing())
		{
#ifdef _DEBUG
			start = std::chrono::steady_clock::now();
#endif // _DEBUG
			m_camera->RetrieveResult(2000, ptrGrabResult, Pylon::TimeoutHandling_ThrowException);
			if (!ptrGrabResult->GrabSucceeded())
			{
				emit errorThrown("[BaslerCamera2] Grab error", ptrGrabResult->GetErrorDescription().c_str());
				continue;
			}

			// version Optimisé Multi thread
			convertAndResize(ptrGrabResult, frame, outImage, m_config->getWidth(), m_config->getHeight());
			//convertGrabResult(ptrGrabResult, frame, outImage);
			
			// sauvegarde thread-safe
			{
				std::scoped_lock lk(m_frameMtx);
				frame.copyTo(m_lastFrame);
			}

#ifdef _DEBUG
			end = std::chrono::steady_clock::now();
			deltaMs = std::chrono::duration<double, std::milli>(end - start).count();
			displayCounter++;
			if (displayCounter == 15)
			{
				qDebug() << deltaMs;
				displayCounter = 0;
			}
#endif // _DEBUG

			emit imageProvided(outImage.copy());   // deep-copy -> sûr pour Qt
		}
	}
	catch (const Pylon::GenericException& e)
	{
		emit errorThrown("[BaslerCamera2] Error", e.GetDescription());
	}
}

void BaslerCamera2::grabEnded()
{
	if (m_task)
	{
		delete m_task;
		m_task = nullptr;
	}
	if (m_watcher)
	{
		delete m_watcher;
		m_watcher = nullptr;
	}
	stopGrabbing();
	m_camera->Close();
}

bool BaslerCamera2::retrieveLastFrame(cv::Mat& dst)
{
	std::scoped_lock lk(m_frameMtx);
	if (m_lastFrame.empty())
		return false;
	m_lastFrame.copyTo(dst);
	return true;
}

//------------- applyConfig --------------------------------------------------
void BaslerCamera2::applyConfig()
{
	if (!m_config || !isOpened())
		return;

	GenApi::INodeMap& nmap = m_camera->GetNodeMap();

	if (auto w = GenApi::CIntegerPtr(nmap.GetNode("Width")))  w->SetValue(m_config->getWidth());
	if (auto h = GenApi::CIntegerPtr(nmap.GetNode("Height"))) h->SetValue(m_config->getHeight());
	if (auto ox = GenApi::CIntegerPtr(nmap.GetNode("OffsetX"))) ox->SetValue(m_config->getOffsetX());
	if (auto oy = GenApi::CIntegerPtr(nmap.GetNode("OffsetY"))) oy->SetValue(m_config->getOffsetY());

	if (auto fmt = GenApi::CEnumerationPtr(nmap.GetNode("PixelFormat")))
		fmt->FromString(m_config->getSelectedFormat().toStdString().c_str());

	if (auto enFps = GenApi::CBooleanPtr(nmap.GetNode("AcquisitionFrameRateEnable")))
		enFps->SetValue(true);
	if (auto fps = GenApi::CFloatPtr(nmap.GetNode("AcquisitionFrameRate")))
		fps->SetValue(m_config->getFps());

	if (auto exp = GenApi::CFloatPtr(nmap.GetNode("ExposureTime")))
		exp->SetValue(m_config->getExposureTime() * 1000);
	if (auto gain = GenApi::CFloatPtr(nmap.GetNode("Gain")))
		gain->SetValue(m_config->getGainDB());
	if (auto wb = GenApi::CEnumerationPtr(nmap.GetNode("BalanceWhiteAuto")))
		wb->FromString("Once");
}

//------------- SDK init/fini -----------------------------------------------
void BaslerCamera2::pylonInit()
{
	if (s_pylonUsers.fetch_add(1) == 0)
		Pylon::PylonInitialize();
}

void BaslerCamera2::pylonTerminate()
{
	if (s_pylonUsers.fetch_sub(1) == 1)
		Pylon::PylonTerminate();
}

// ---------------------------------------
// Optimized convert result methods
// ---------------------------------------

void BaslerCamera2::demosaicPixel(const uint8_t* bayer, int& x, int& y, const int& width, const int& height, const int& stride, bool& rowEven, bool& colEven, uint8_t& B, uint8_t& G, uint8_t& R)
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

void BaslerCamera2::convertAndResize(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight)
{
	int xMid = newWidth / 2;
	int yMid = newHeight / 2;

	auto task1 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResizeTask(ptrGrabResult, outFrame, outImage, newWidth, newHeight, 0, xMid, 0, yMid);
		});

	auto task2 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResizeTask(ptrGrabResult, outFrame, outImage, newWidth, newHeight, xMid, newWidth, 0, yMid);
		});

	auto task3 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResizeTask(ptrGrabResult, outFrame, outImage, newWidth, newHeight, 0, xMid, yMid, newHeight);
		});

	auto task4 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &newWidth, &newHeight, &xMid, &yMid]() {
		convertAndResizeTask(ptrGrabResult, outFrame, outImage, newWidth, newHeight, xMid, newWidth, yMid, newHeight);
		});

	// Attendre que tout soit terminé
	task1.waitForFinished();
	task2.waitForFinished();
	task3.waitForFinished();
	task4.waitForFinished();
}
void BaslerCamera2::convertAndResizeTask(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int& newWidth, int& newHeight, int xStart, int xEnd, int yStart, int yEnd)
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

			demosaicPixel(srcBuffer, srcX, srcY, srcWidth, srcHeight, stride, rowEven, colEven, B, G, R);

			// Écriture OpenCV
			//cv::Vec3b& pixel = outFrame.at<cv::Vec3b>(dstY + offsetY, dstX + offsetX);
			cv::Vec3b& pixel = outRow[dstX + offsetX];
			pixel[0] = B;
			pixel[1] = G;
			pixel[2] = R;

			// Écriture QImage (format RGB888 -> ordre: R, G, B)
			qPixel = &imgRow[(dstX + offsetX) * 3];
			qPixel[0] = R;
			qPixel[1] = G;
			qPixel[2] = B;
		}
	}
}

void BaslerCamera2::convertGrabResult(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage)
{
	int width = ptrGrabResult->GetWidth();
	int height = ptrGrabResult->GetWidth();
	int xMid = width / 2;
	int yMid = height / 2;

	auto task1 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &width, &height, &xMid, &yMid]() {
		convertGrabResultTask(ptrGrabResult, outFrame, outImage, 0, xMid, 0, yMid);
		});

	auto task2 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &width, &height, &xMid, &yMid]() {
		convertGrabResultTask(ptrGrabResult, outFrame, outImage, xMid, width, 0, yMid);
		});

	auto task3 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &width, &height, &xMid, &yMid]() {
		convertGrabResultTask(ptrGrabResult, outFrame, outImage, 0, xMid, yMid, height);
		});

	auto task4 = QtConcurrent::run([this, &ptrGrabResult, &outFrame, &outImage, &width, &height, &xMid, &yMid]() {
		convertGrabResultTask(ptrGrabResult, outFrame, outImage, xMid, width, yMid, height);
		});

	// Attendre que tout soit terminé
	task1.waitForFinished();
	task2.waitForFinished();
	task3.waitForFinished();
	task4.waitForFinished();
}

void BaslerCamera2::convertGrabResultTask(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int xStart, int xEnd, int yStart, int yEnd)
{
	const int srcWidth = ptrGrabResult->GetWidth();
	const int srcHeight = ptrGrabResult->GetHeight();
	const int stride = ptrGrabResult->GetPaddingX() + srcWidth;

	const uint8_t* srcBuffer = static_cast<uint8_t*>(ptrGrabResult->GetBuffer());

	int currentX;
	int currentY;
	uint8_t B, G, R;

	bool rowEven;
	bool colEven;
	cv::Vec3b* outRow;
	uint8_t* imgRow;
	uint8_t* qPixel;

	for (currentY = yStart; currentY < yEnd; ++currentY)
	{
		rowEven = (currentY % 2) == 0;
		outRow = outFrame.ptr<cv::Vec3b>(currentY);
		imgRow = outImage.scanLine(currentY);

		for (currentX = xStart; currentX < xEnd; ++currentX)
		{
			colEven = (currentX % 2) == 0;

			demosaicPixel(srcBuffer, currentX, currentY, srcWidth, srcHeight, stride, rowEven, colEven, B, G, R);

			// Écriture OpenCV
			//cv::Vec3b& pixel = outFrame.at<cv::Vec3b>(dstY, dstX);
			cv::Vec3b& pixel = outRow[currentX];
			pixel[0] = B;
			pixel[1] = G;
			pixel[2] = R;

			// Écriture QImage (format RGB888 -> ordre: R, G, B)
			qPixel = &imgRow[currentX * 3];
			qPixel[0] = R;
			qPixel[1] = G;
			qPixel[2] = B;
		}
	}
}
