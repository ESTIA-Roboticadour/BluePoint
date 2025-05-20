#pragma once
#include <QObject>
#include <QImage>

class ImageProvider : public QObject
{
	Q_OBJECT
public:
	explicit ImageProvider(QObject* parent = nullptr);
	~ImageProvider() = default;

signals:
	void imageProvided(const QImage& image);
};
