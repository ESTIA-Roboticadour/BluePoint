#pragma once
#include "ImageProvider.h"
#include "ImageTransformer.h"

#include <QObject>
#include <QList>

class Camera : public ImageProvider
{
	Q_OBJECT
public :
	explicit Camera(QObject* parent = nullptr);
	~Camera() = default;

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

private:
	QList<ImageTransformer*> m_transformers;
};
