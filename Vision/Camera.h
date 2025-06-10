#pragma once
#include "ImageProvider.h"
#include "ImageTransformer.h"
#include "CameraConfig.h"

#include <QObject>
#include <QList>
#include <opencv2/core.hpp>        // cv::Mat
#include <opencv2/imgproc.hpp>

class Camera : public ImageProvider
{
	Q_OBJECT
public :
	explicit Camera(QObject* parent = nullptr);
	~Camera() = default;

	virtual void setConfig(const CameraConfig* cfg) = 0;

	virtual bool isConnected() const = 0;
	virtual bool isOpened() const = 0;

	virtual void connect() = 0;
	virtual void disconnect() = 0;

	virtual void open(const CameraConfig* cfg = nullptr) = 0;
	virtual void close() = 0;

	virtual bool retrieveLastFrame(cv::Mat& dst) = 0;

	virtual void release();
	bool isReleased() const;

	//void addTransformer(ImageTransformer* t);
	//void clearTransformers(bool deleteTransformers=false);
	//QList<ImageTransformer*> transformers() const;

//protected:
//	QImage applyPipeline(const QImage& raw);
//	bool hasTransformer() const;

signals:
	//void transformError(ImageTransformer* transformer, const int index, const QString& message);
	void released();
	void connected();
	void disconnected();
	void opened();
	void closed();
	void failedToConnect(const QString& message);
	void failedToDisconnect(const QString& message);
	void failedToOpen(const QString& message);
	void failedToClose(const QString& message);
	void errorThrown(const QString& error, const QString& message);
	void cvFrameReady();
//private:
//	QList<ImageTransformer*> m_transformers;

private:
	bool m_isReleased;
};
