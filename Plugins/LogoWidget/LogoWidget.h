#ifndef LOGOWIDGET_H
#define LOGOWIDGET_H

#include "LogoWidget_global.h"

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QColor>
#include <algorithm>

class LOGOWIDGET_API LogoWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPixmap logoPixmap  READ logoPixmap    WRITE setLogoPixmap    NOTIFY logoPixmapChanged)
    Q_PROPERTY(int     logoWidth   READ logoWidth     WRITE setLogoWidth     NOTIFY logoSizeChanged)
    Q_PROPERTY(int     logoHeight  READ logoHeight    WRITE setLogoHeight    NOTIFY logoSizeChanged)

public:
    explicit LogoWidget(QWidget* parent = nullptr);
    ~LogoWidget() = default;

    void setSize(int targetSize, Qt::TransformationMode mode = Qt::SmoothTransformation);
    void setSize(int width, int height, Qt::TransformationMode mode = Qt::SmoothTransformation);

    QPixmap logoPixmap() const       { return m_original; }
    int     logoWidth() const        { return m_width; }
    int     logoHeight() const       { return m_height; }

public slots:
    void setLogoPixmap(const QPixmap& px);
    void setLogoWidth(int w);
    void setLogoHeight(int h);

signals:
    void logoPixmapChanged(const QPixmap& logoPixmap);
    void logoSizeChanged();

private:
    void updatePixmap(Qt::TransformationMode mode = Qt::SmoothTransformation);

    QLabel*  m_logoLabel { nullptr };
    QPixmap  m_original;
    int      m_width  { 128 };
    int      m_height { 128 };
};

#endif // LOGOWIDGET_H
