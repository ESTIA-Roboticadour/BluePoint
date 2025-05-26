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
    Q_PROPERTY(QString logoPath    READ logoPath      WRITE setLogoPath      NOTIFY logoPathChanged)
    Q_PROPERTY(int     logoWidth   READ logoWidth     WRITE setLogoWidth     NOTIFY logoSizeChanged)
    Q_PROPERTY(int     logoHeight  READ logoHeight    WRITE setLogoHeight    NOTIFY logoSizeChanged)

public:
    explicit LogoWidget(QWidget* parent = nullptr);
    ~LogoWidget() = default;

    void setSize(int targetSize, Qt::TransformationMode mode = Qt::SmoothTransformation);
    void setSize(int width, int height, Qt::TransformationMode mode = Qt::SmoothTransformation);

    QString logoPath()  const        { return m_logoPath; }
    int     logoWidth() const        { return m_width; }
    int     logoHeight() const       { return m_height; }

public slots:
    void setLogoPath(const QString& path);
    void setLogoWidth(int w);
    void setLogoHeight(int h);

signals:
    void logoPathChanged(const QString&);
    void logoSizeChanged();

private:
    void updatePixmap(Qt::TransformationMode mode = Qt::SmoothTransformation);

    QLabel*  m_logoLabel { nullptr };
    QPixmap  m_original;
    QString  m_logoPath;
    int      m_width  { 128 };
    int      m_height { 128 };
};

#endif // LOGOWIDGET_H
