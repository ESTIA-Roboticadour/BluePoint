#include "LogoWidget.h"
#include <QVBoxLayout>

LogoWidget::LogoWidget(QWidget* parent) :
    QWidget(parent),
    m_logoLabel(new QLabel(this)),
    m_logoPath(),
    m_width(128),
    m_height(128)
{
    /* charge le pixmap d’origine */
    //setLogoPath(m_logoPath);

    m_logoLabel->setAlignment(Qt::AlignCenter);

    auto* lay = new QVBoxLayout(this);
    lay->addWidget(m_logoLabel);
    lay->setAlignment(Qt::AlignCenter);
    setLayout(lay);
}

/* ------------------------------------------------------------------ */
/* API “setSize” historique                                           */
/* ------------------------------------------------------------------ */
void LogoWidget::setSize(int targetSize, Qt::TransformationMode mode)
{
    setSize(targetSize, targetSize, mode);
}

void LogoWidget::setSize(int w, int h, Qt::TransformationMode mode)
{
    if (w == m_width && h == m_height)
        return;

    m_width  = std::max(1, w);
    m_height = std::max(1, h);
    updatePixmap(mode);
    emit logoSizeChanged();
}

/* ------------------------------------------------------------------ */
/* setters Designer                                                   */
/* ------------------------------------------------------------------ */
void LogoWidget::setLogoPath(const QString& path)
{
    if (path.isEmpty() || path == m_logoPath)
        return;

    QPixmap pm(path);                  // charge à partir d’un fichier OU d’une ressource
    if (pm.isNull())
        return;                        // on ignore les chemins invalides

    m_logoPath  = path;
    m_original  = pm;
    updatePixmap();
    emit logoPathChanged(m_logoPath);
}

void LogoWidget::setLogoWidth(int w)  { setSize(w, m_height); }
void LogoWidget::setLogoHeight(int h) { setSize(m_width, h); }

/* ------------------------------------------------------------------ */
/* helper                                                             */
/* ------------------------------------------------------------------ */
void LogoWidget::updatePixmap(Qt::TransformationMode mode)
{
    if (m_original.isNull())
        m_original = QPixmap(m_logoPath);     // en dernier recours

    m_logoLabel->setPixmap(m_original.scaled(m_width,
                                             m_height,
                                             Qt::KeepAspectRatio,
                                             mode));
}
