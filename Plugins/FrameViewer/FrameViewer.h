#ifndef FRAMEVIEWER_H
#define FRAMEVIEWER_H

#include "FrameViewer_global.h"

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QString>
#include <QTransform>

class FRAMEVIEWER_API FrameViewer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit FrameViewer(QWidget *parent = nullptr);

    QString source() const;
    void setSource(const QString &path);

    void setImage(const QImage &img);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    Qt::TransformationMode transformationMode() const;
    void setTransformationMode(Qt::TransformationMode mode);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QSize findScaledSizeKeepingAspectRatio(const QSize& original, const QSize& maxSize);
    void updateScaledImage();

private:
    QImage m_image;
    QImage m_scaledImage;
    QString m_source;
    QColor m_backgroundColor;
    Qt::TransformationMode m_transformationMode;
};

#endif // FRAMEVIEWER_H
