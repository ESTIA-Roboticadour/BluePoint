#pragma once
#include <QObject>
#include <QImage>

class ImageTransformer : public QObject
{
	Q_OBJECT
public:
	explicit ImageTransformer(QObject* parent = nullptr);
	virtual ~ImageTransformer() = default;

	virtual QImage transform(const QImage& image) = 0;
};
