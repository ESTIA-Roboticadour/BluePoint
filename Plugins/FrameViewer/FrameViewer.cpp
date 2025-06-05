#include "FrameViewer.h"
#include <QPainter>
#include <QResizeEvent>
#include <QFile>

FrameViewer::FrameViewer(QWidget *parent):
    QWidget(parent),
    m_image(),
    m_scaledImage(),
    m_source(""),
    m_backgroundColor(Qt::black),
    m_transformationMode(Qt::FastTransformation)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QString FrameViewer::source() const
{
    return m_source;
}

void FrameViewer::setSource(const QString &path)
{
    if (!QFile::exists(path))
        return;

    QImage img;
    if (img.load(path))
    {
        m_image = img;
        m_source = path;
        updateScaledImage();
        update();
    }
}

void FrameViewer::setImage(const QImage &img)
{
    clear();
    m_image = img;
    updateScaledImage();
    update();
}

void FrameViewer::clear()
{
    m_source.clear();
    m_image = QImage();
    m_scaledImage = m_image;
    update();
}

QColor FrameViewer::backgroundColor() const
{
    return m_backgroundColor;
}

void FrameViewer::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update();
}

Qt::TransformationMode FrameViewer::transformationMode() const
{
    return m_transformationMode;
}

void FrameViewer::setTransformationMode(Qt::TransformationMode mode)
{
    if (m_transformationMode != mode)
    {
        m_transformationMode = mode;
        updateScaledImage();
        update();
    }
}

void FrameViewer::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateScaledImage();
}

QSize FrameViewer::findScaledSizeKeepingAspectRatio(const QSize& original, const QSize& maxSize)
{
    int newWidth;
    int newHeight;

    if (original.width() == 0 || original.height() == 0 || maxSize.width() == 0 || maxSize.height() == 0)
    {
        newWidth = 0;
        newHeight = 0;
    }
    else
    {
        float originalWidth = (float)original.width();
        float originalHeight = (float)original.height();

        float ratioWidth = originalWidth / (float)maxSize.width();
        float ratioHeight = originalHeight / (float)maxSize.height();

        if (ratioWidth > ratioHeight)
        {
            newWidth = maxSize.width();
            newHeight = (int)std::roundf(originalHeight / ratioWidth);
        }
        else
        {
            newHeight = maxSize.height();
            newWidth = (int)std::roundf(originalWidth / ratioHeight);
        }
    }
    return QSize(newWidth, newHeight);
}

void FrameViewer::updateScaledImage()
{
    emit beforeUpdateImage();
    if (m_image.isNull())
    {
        m_scaledImage = QImage();
        return;
    }
    QSize scaledSize = findScaledSizeKeepingAspectRatio(m_image.size(), size());
    if (m_scaledImage.size() == scaledSize)
        return;

    m_scaledImage = m_image.scaled(scaledSize, Qt::IgnoreAspectRatio, m_transformationMode);
    emit afterUpdateImage();
}

void FrameViewer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), m_backgroundColor);

    if (!m_scaledImage.isNull())
    {
        int x = (width() - m_scaledImage.width()) / 2;
        int y = (height() - m_scaledImage.height()) / 2;
        painter.drawImage(QPoint(x, y), m_scaledImage);
    }
}
