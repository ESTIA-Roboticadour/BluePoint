#pragma once
#include "ImageTransformer.h"
#include "NumericalParameter.h"
#include "RoiConfig.h"

#include <QImage>

class RoiTransformer : public ImageTransformer
{
	Q_OBJECT
public:
	explicit RoiTransformer(QObject* parent = nullptr);
	RoiTransformer(RoiConfig* config, QObject* parent = nullptr);
	~RoiTransformer() = default;

	RoiConfig* getConfig();
	void setConfig(RoiConfig* config);
	QImage transform(const QImage& image) override;

private:
	RoiConfig* m_config;
};
