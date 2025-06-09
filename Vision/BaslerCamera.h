#pragma once

#include "Camera.h"
#include "BaslerCameraConfig.h"

#include <pylon/PylonIncludes.h>   // API Pylon C++
#include <opencv2/core.hpp>        // cv::Mat

#include <memory>
#include <atomic>
#include <mutex>

class BaslerCamera final : public Camera
{
    Q_OBJECT
public:
    explicit BaslerCamera(QObject* parent = nullptr);
    ~BaslerCamera() override;

    // Configuration
    void setConfig(const CameraConfig* cfg) override;
    void setConfig(const BaslerCameraConfig* cfg);

    // API Camera
    bool isConnected() const override;
    bool isOpened()   const override;
    void connect()    override;
    void disconnect() override;
    void open(const CameraConfig* cfg = nullptr)       override;
    void close()      override;

    // Grabbing
    void startGrabbing(Pylon::EGrabStrategy strat = Pylon::GrabStrategy_LatestImageOnly, Pylon::EGrabLoop loop = Pylon::GrabLoop_ProvidedByUser);
    void stopGrabbing();
    bool retrieveLastFrame(cv::Mat& dst) override;
	bool isGrabbing() const { return m_cam && m_cam->IsGrabbing(); }

private:
    void applyConfig();
    static void pylonInit();               ///< init ref-countée
    static void pylonFini();

    std::unique_ptr<Pylon::CInstantCamera> m_cam;
    const BaslerCameraConfig* m_cfg{ nullptr };

    static std::atomic_int s_pylonUsers;

    mutable std::mutex m_frameMtx;
    cv::Mat            m_lastFrame;
};
