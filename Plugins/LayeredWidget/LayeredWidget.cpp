#include "LayeredWidget.h"
#include <QGraphicsOpacityEffect>
#include <QResizeEvent>
#include <utility>      // std::swap

namespace {
    inline void makeChild(QWidget* child, QWidget* parent)
    {
        if (!child) 
            return;
        child->setParent(parent);
        child->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        child->show();
    }
}

LayeredWidget::LayeredWidget(QWidget* parent) :
    QWidget(parent),
	m_back(nullptr),
	m_front(nullptr),
	m_filter(nullptr),
    m_backOpacity(0.5),
    m_filterColor(Qt::black),
    m_filterAlpha(0.5)
{
}

void LayeredWidget::setBackgroundWidget(QWidget* w, bool deleteOld)
{
    if (m_back == w) return;

    if (m_back)
    {
        m_back->setParent(nullptr);   // libère l'ancien mais ne le détruit pas
        if (deleteOld) 
            m_back->deleteLater();
    }
    m_back = w;
    makeChild(m_back, this);
    applyOpacity();
    updateGeometryAndStacking();
}

void LayeredWidget::setForegroundWidget(QWidget* w, bool deleteOld)
{
    if (m_front == w) return;

    if (m_front)
    {
        m_front->setParent(nullptr);
        if (deleteOld)
            m_front->deleteLater();
    }
    m_front = w;
    makeChild(m_front, this);
    updateGeometryAndStacking();
}

void LayeredWidget::swapLayers()
{
    std::swap(m_back, m_front);
    applyOpacity();
    updateGeometryAndStacking();
}

qreal LayeredWidget::backgroundOpacity() const { return m_backOpacity; }

void LayeredWidget::setBackgroundOpacity(qreal alpha)
{
    alpha = std::clamp(alpha, 0.0, 1.0);
    if (qFuzzyCompare(alpha, m_backOpacity))
        return;

    m_backOpacity = alpha;
    applyOpacity();
    emit backgroundOpacityChanged(alpha);
}

/* ------------------------------------------------------------------ */
/* filtre : propriétés Designer                                       */
/* ------------------------------------------------------------------ */
QColor LayeredWidget::filterColor() const     { return m_filterColor; }
qreal  LayeredWidget::filterOpacity() const   { return m_filterAlpha; }

void LayeredWidget::setFilterColor(const QColor& c)
{
    setFilter(c, m_filterAlpha);                     // conserve l’opacité
}

void LayeredWidget::setFilterOpacity(qreal alpha)
{
    setFilter(m_filterColor, alpha);                 // conserve la couleur
}

void LayeredWidget::setFilter(const QColor& c, qreal alpha)
{
    alpha = std::clamp(alpha, 0.0, 1.0);
    if (c == m_filterColor && qFuzzyCompare(alpha, m_filterAlpha))
        return;

    m_filterColor  = c;
    m_filterAlpha  = alpha;

    ensureFilterExists();
    QColor col = m_filterColor;
    col.setAlphaF(m_filterAlpha);
    m_filter->setStyleSheet(QStringLiteral("background:%1;").arg(col.name(QColor::HexArgb)));

    updateGeometryAndStacking();
    emit filterColorChanged(m_filterColor);
    emit filterOpacityChanged(m_filterAlpha);
}

void LayeredWidget::ensureFilterExists()
{
    if (!m_filter) {
        m_filter = new QWidget(this);
        m_filter->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        m_filter->show();
    }
}

void LayeredWidget::clearFilter()
{
    if (m_filter) {
        delete m_filter;
        m_filter = nullptr;
    }
    if (m_filterAlpha != 0.0) {
        m_filterAlpha = 0.0;
        emit filterOpacityChanged(0.0);
    }
}

void LayeredWidget::applyOpacity()
{
    if (!m_back) return;

    auto* eff = qobject_cast<QGraphicsOpacityEffect*>(m_back->graphicsEffect());
    if (!eff)
    {
        eff = new QGraphicsOpacityEffect(this);
        m_back->setGraphicsEffect(eff);
    }
    eff->setOpacity(m_backOpacity);
}

void LayeredWidget::updateGeometryAndStacking()
{
    // ordre : background (le plus bas), filtre, foreground (haut)
    if (m_back)   m_back->lower();
    if (m_filter) m_filter->raise();
    if (m_front)  m_front->raise();

    const QRect r = rect();
    if (m_back)   m_back->setGeometry(r);
    if (m_filter) m_filter->setGeometry(r);
    if (m_front)  m_front->setGeometry(r);

    update();   // cas où aucun child => on pourrait dessiner quelque chose
}

void LayeredWidget::resizeEvent(QResizeEvent* e)
{
    updateGeometryAndStacking();
    QWidget::resizeEvent(e);
}
