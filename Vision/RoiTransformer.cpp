#include "RoiTransformer.h"

RoiTransformer::RoiTransformer(QObject* parent) :
	ImageTransformer(parent),
	m_config(new RoiConfig(this))
{
}

RoiTransformer::RoiTransformer(RoiConfig* config, QObject* parent) :
	ImageTransformer(parent),
	m_config(config ? config : new RoiConfig(this))
{
}

RoiConfig* RoiTransformer::getConfig()
{
	return m_config;
}

void RoiTransformer::setConfig(RoiConfig* config)
{
	m_config = config;
}

QImage RoiTransformer::transform(const QImage& image)
{
	// 1) V�rification de l�image en entr�e
	if (!m_config || image.isNull())
		return image;

	// 2) R�cup�ration du ROI demand� (x, y, w, h)
	QRect roi = m_config->getRoi();

	if (!roi.isValid())
		return image;

	// 3) Adaptation aux limites de l�image
	//    image.rect() == QRect(0, 0, image.width(), image.height())
	roi = roi.intersected(image.rect());

	// 4) Si le ROI est en dehors de l�image ou nul, retourner vide
	if (roi.isEmpty())
		return QImage();

	// 5) Recadrage : QImage::copy cr�e d�j� une nouvelle image
	return image.copy(roi);
}
