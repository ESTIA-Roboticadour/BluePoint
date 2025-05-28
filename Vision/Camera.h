#pragma once
#include "ImageProvider.h"
#include "ImageTransformer.h"
#include "CameraConfig.h"

#include <QObject>
#include <QList>

class Camera : public ImageProvider
{
	Q_OBJECT
public :
	explicit Camera(QObject* parent = nullptr);
	~Camera() = default;

	CameraConfig* getConfig() const;
	void setConfig(CameraConfig* config);

	virtual bool isConnected() const = 0;
	virtual bool isOpened() const = 0;

	virtual void connect() = 0;
	virtual void disconnect() = 0;

	virtual void open() = 0;
	virtual void close() = 0;

	void addTransformer(ImageTransformer* t);
	void clearTransformers(bool deleteTransformers=false);
	QList<ImageTransformer*> transformers() const;

protected:
	QImage applyPipeline(const QImage& raw);

signals:
	void transformError(ImageTransformer* transformer, const int index, const QString& message);
	void connected();
	void disconnected();
	void opened();
	void closed();
	void failedToConnect(const QString& message);
	void failedToDisconnect(const QString& message);
	void failedToOpen(const QString& message);
	void failedToClose(const QString& message);
	void errorThrown(const QString& error, const QString& message);

private:
	QList<ImageTransformer*> m_transformers;
	CameraConfig* m_config;
};
