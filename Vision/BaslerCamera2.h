#pragma once

#include "Camera.h"
#include "BaslerCameraConfig.h"

#include <QFuture>
#include <QFutureWatcher>

#include <pylon/PylonIncludes.h>   // API Pylon C++
#include <opencv2/core.hpp>        // cv::Mat

#include <memory>
#include <atomic>
#include <mutex>

class BaslerCamera2 final : public Camera
{
    Q_OBJECT
public:
    explicit BaslerCamera2(QObject* parent = nullptr);
    ~BaslerCamera2() override;

    void release();

    // Configuration
    void setConfig(const CameraConfig* cfg) override;
    void setConfig(const BaslerCameraConfig* cfg);

    // API Camera
    bool isConnected() const override;
    bool isOpened()   const override;
    void connect()    override;
    void disconnect() override;
    void open(const CameraConfig* cfg = nullptr) override;
    void close()      override;

    // Grabbing
    bool retrieveLastFrame(cv::Mat& dst) override;
    bool isGrabbing() const { return m_camera && m_camera->IsGrabbing(); }

private slots:
    void grabLoop();
    void grabEnded();

private:
    void applyConfig();
    // Grabbing
    void startGrabbing();
    void stopGrabbing();

    // Optimized convert result methods
    // Fonction pour estimer B, G, R à partir du Bayer
    void demosaicPixel(const uint8_t* bayer, int& x, int& y, const int& width, const int& height, const int& stride, bool& rowEven, bool& colEven, uint8_t& B, uint8_t& G, uint8_t& R);
    void convertAndResize(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int newWidth, int newHeight);
    void convertAndResizeTask(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int& newWidth, int& newHeight, int xStart, int xEnd, int yStart, int yEnd);
    void convertGrabResult(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage);
    void convertGrabResultTask(const Pylon::CGrabResultPtr& ptrGrabResult, cv::Mat& outFrame, QImage& outImage, int xStart, int xEnd, int yStart, int yEnd);

    static void pylonInit();               ///< init ref-countée
    static void pylonTerminate();

private:
    std::unique_ptr<Pylon::CInstantCamera> m_camera;
    const BaslerCameraConfig* m_config{ nullptr };

    static std::atomic_int s_pylonUsers;

    QFuture<void>*        m_task;
    QFutureWatcher<void>* m_watcher;
    mutable std::mutex    m_frameMtx;
    cv::Mat               m_lastFrame;

    bool m_isReleased;
    bool m_isReleasing;
};
