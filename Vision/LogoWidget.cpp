#include "LogoWidget.h"

LogoWidget::LogoWidget(QWidget* parent) :
    QWidget(parent),
    logoLabel(new QLabel(this))
{
    QPixmap logo(":/VisionWindow/Resources/icon.png");

    logoLabel->setPixmap(logo);
    logoLabel->setAlignment(Qt::AlignCenter);

    auto* lay = new QVBoxLayout(this);
    lay->addWidget(logoLabel);
    lay->setAlignment(Qt::AlignCenter);
    setLayout(lay);
}

void LogoWidget::setSize(int targetSize, Qt::TransformationMode mode)
{
	setSize(targetSize, targetSize, mode);
}

void LogoWidget::setSize(int width, int height, Qt::TransformationMode mode)
{
    logoLabel->setPixmap(logoLabel->pixmap().scaled(width, height, Qt::KeepAspectRatio, mode));
}
