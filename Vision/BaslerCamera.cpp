#include "BaslerCamera.h"

#include <pylon/PylonUtilityIncludes.h>   // CPylonImage, CImageFormatConverter
#include <GenApi/GenApi.h>                // NodeMap helpers
#include <QImage>
#include <QString>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <chrono>

//------------- init static --------------------------------------------------
std::atomic_int BaslerCamera::s_pylonUsers{ 0 };

//------------- ctor / dtor --------------------------------------------------
BaslerCamera::BaslerCamera(QObject* parent) : Camera(parent)
{
	pylonInit();
}

BaslerCamera::~BaslerCamera()
{
	if (isOpened())
		close();
	if (isConnected())
		disconnect();
	pylonFini();
}

void BaslerCamera::setConfig(const CameraConfig* cfg)
{
	if (auto* baslerCfg = dynamic_cast<const BaslerCameraConfig*>(cfg))
	{
		setConfig(baslerCfg);
	}
	else
	{
		qWarning() << "[BaslerCamera] Invalid config type, expected BaslerCameraConfig";
	}
}

//------------- config -------------------------------------------------------
void BaslerCamera::setConfig(const BaslerCameraConfig* cfg)
{
	m_cfg = cfg;
	if (isOpened())
		applyConfig();
}

//------------- status -------------------------------------------------------
bool BaslerCamera::isConnected() const { return m_cam && m_cam->IsPylonDeviceAttached(); }
bool BaslerCamera::isOpened()   const { return m_cam && m_cam->IsOpen(); }

//------------- connect / disconnect ----------------------------------------
void BaslerCamera::connect()
{
	if (isConnected())
		return;

	try
	{
		m_cam = std::make_unique<Pylon::CInstantCamera>(Pylon::CTlFactory::GetInstance().CreateFirstDevice());
		emit connected();
	}
	catch (const Pylon::GenericException& e)
	{
		emit failedToConnect(tr("[BaslerCamera] Failed to connect:") + e.GetDescription());
		m_cam.reset();
	}
}

void BaslerCamera::disconnect()
{
	if (!isConnected())
		return;

	try
	{
		close();
		m_cam->DetachDevice();
		m_cam.reset();
		emit disconnected();
	}
	catch (const Pylon::GenericException& e)
	{
		emit failedToDisconnect(tr("[BaslerCamera] Failed to disconnect:") + e.GetDescription());
	}
}

//------------- open / close -------------------------------------------------
void BaslerCamera::open(const CameraConfig* cfg)
{
	if (!isConnected())
	{
		emit failedToOpen("[BaslerCamera] Failed to open: Camera not connected");
		return;
	}
	if (!isOpened())
	{
		try
		{
			try
			{
				m_cam->Open();
			}
			catch (const Pylon::GenericException& e)
			{
				emit failedToOpen(tr("[BaslerCamera] Failed to open: ") + e.GetDescription());
				return;
			}

			if (m_cam->IsOpen())
			{
				if (cfg)
				{
					try
					{
						setConfig(cfg);
					}
					catch (const Pylon::GenericException& e)
					{
						emit failedToOpen(tr("[BaslerCamera] Invalid configuration: ") + e.GetDescription());
						close();
						return;
					}
				}
				startGrabbing();
				if (isGrabbing())
				{
					emit opened();
				}
				else
				{
					emit failedToOpen("[BaslerCamera] Failed to start grabbing");
					close();
				}
			}
			else
			{
				emit failedToOpen("[BaslerCamera] Failed to close");
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

void BaslerCamera::close()
{
	if (!isOpened())
		return;

	try
	{
		stopGrabbing();
		m_cam->Close();
		emit closed();
	}
	catch (const Pylon::GenericException& e)
	{
		emit failedToClose(tr("[BaslerCamera] Failed to close: ") + e.GetDescription());
	}
}

//------------- grabbing -----------------------------------------------------
void BaslerCamera::startGrabbing(Pylon::EGrabStrategy strat, Pylon::EGrabLoop loop)
{
	if (!isOpened())
		return;

	if (isGrabbing())
		return;

	m_cam->MaxNumBuffer = 10;
	m_cam->StartGrabbing(strat, loop);

	std::thread([this]
		{
			Pylon::CGrabResultPtr        ptr;
			Pylon::CImageFormatConverter conv;
			conv.OutputPixelFormat = Pylon::PixelType_BGR8packed;
			Pylon::CPylonImage           pyImg;
			cv::Mat                      matRGB;

#ifdef _DEBUG
			std::chrono::steady_clock::time_point start;
			std::chrono::steady_clock::time_point end;
			double deltaMs;
			int displayCounter = 0;
#endif // _DEBUG

			while (m_cam && m_cam->IsGrabbing())
			{
				try
				{
#ifdef _DEBUG
					start = std::chrono::steady_clock::now();
#endif // _DEBUG
					m_cam->RetrieveResult(2000, ptr, Pylon::TimeoutHandling_ThrowException);
					if (!ptr->GrabSucceeded())
					{
						emit errorThrown("[BaslerCamera] Grab error 1", ptr->GetErrorDescription().c_str());
						continue;
					}

					// BGR header sur buffer Pylon
					conv.Convert(pyImg, ptr);

					cv::Mat matBGR(ptr->GetHeight(), ptr->GetWidth(), CV_8UC3,
						const_cast<std::uint8_t*>(
							static_cast<const std::uint8_t*>(pyImg.GetBuffer())),
						ptr->GetWidth() * 3);

					// BGR -> RGB (tampon ré-utilisable)
					matRGB.create(matBGR.rows, matBGR.cols, CV_8UC3);
					cv::cvtColor(matBGR, matRGB, cv::COLOR_BGR2RGB);

					// sauvegarde thread-safe
					{
						std::scoped_lock lk(m_frameMtx);
						matRGB.copyTo(m_lastFrame);
					}

					// QImage
					QImage image(matRGB.data, matRGB.cols, matRGB.rows, static_cast<int>(matRGB.step), QImage::Format_RGB888);

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

					emit imageProvided(image.copy());   // deep-copy -> sûr pour Qt

					// si besoin d'un signal OpenCV :
					emit cvFrameReady();

				}
				catch (const Pylon::GenericException& e)
				{
					emit errorThrown("[BaslerCamera] Grab error 2", e.GetDescription());
					continue;
				}
			}
		}).detach();
}

void BaslerCamera::stopGrabbing()
{
	if (isGrabbing())
		m_cam->StopGrabbing();
}

bool BaslerCamera::retrieveLastFrame(cv::Mat& dst)
{
	std::scoped_lock lk(m_frameMtx);
	if (m_lastFrame.empty())
		return false;
	m_lastFrame.copyTo(dst);
	return true;
}

//------------- applyConfig --------------------------------------------------
void BaslerCamera::applyConfig()
{
	if (!m_cfg || !isOpened())
		return;

	GenApi::INodeMap& nmap = m_cam->GetNodeMap();

	if (auto w = GenApi::CIntegerPtr(nmap.GetNode("Width")))  w->SetValue(m_cfg->getWidth());
	if (auto h = GenApi::CIntegerPtr(nmap.GetNode("Height"))) h->SetValue(m_cfg->getHeight());
	if (auto ox = GenApi::CIntegerPtr(nmap.GetNode("OffsetX"))) ox->SetValue(m_cfg->getOffsetX());
	if (auto oy = GenApi::CIntegerPtr(nmap.GetNode("OffsetY"))) oy->SetValue(m_cfg->getOffsetY());

	if (auto fmt = GenApi::CEnumerationPtr(nmap.GetNode("PixelFormat")))
		fmt->FromString(m_cfg->getSelectedFormat().toStdString().c_str());

	if (auto enFps = GenApi::CBooleanPtr(nmap.GetNode("AcquisitionFrameRateEnable")))
		enFps->SetValue(true);
	if (auto fps = GenApi::CFloatPtr(nmap.GetNode("AcquisitionFrameRate")))
		fps->SetValue(m_cfg->getFps());

	if (auto exp = GenApi::CFloatPtr(nmap.GetNode("ExposureTime")))
		exp->SetValue(m_cfg->getExposureTime() * 1000);
	if (auto gain = GenApi::CFloatPtr(nmap.GetNode("Gain")))
		gain->SetValue(m_cfg->getGainDB());
	if (auto wb = GenApi::CEnumerationPtr(nmap.GetNode("BalanceWhiteAuto")))
		wb->FromString("Once");
}

//------------- SDK init/fini -----------------------------------------------
void BaslerCamera::pylonInit()
{
	if (s_pylonUsers.fetch_add(1) == 0)
		Pylon::PylonInitialize();
}

void BaslerCamera::pylonFini()
{
	if (s_pylonUsers.fetch_sub(1) == 1)
		Pylon::PylonTerminate();
}
