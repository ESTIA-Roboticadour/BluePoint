#include "TransparentScrollArea.h"

#include <QPainter>

TransparentScrollArea::TransparentScrollArea(QWidget* parent) :
    QWidget(parent),
    m_scrollArea(new QScrollArea(this)),
    m_bgColor()
{
    m_bgColor = palette().color(QPalette::Window);
    m_bgColor.setAlpha(204); // opacity: 80%

    // Ensure we paint our own background only.
    setAttribute(Qt::WA_OpaquePaintEvent, false);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAutoFillBackground(false);

    // ScrollArea setup.
    m_scrollArea->setFrameShape(QFrame::NoFrame);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->viewport()->setAttribute(Qt::WA_TranslucentBackground);
    m_scrollArea->viewport()->setAutoFillBackground(false);

    // Layout takes full space.
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_scrollArea);
}

void TransparentScrollArea::setBackgroundColor(const QColor& color)
{
    if (m_bgColor == color)
        return;

    m_bgColor.setRed(color.red());
    m_bgColor.setGreen(color.green());
    m_bgColor.setBlue(color.blue());
    update();
}

void TransparentScrollArea::setBackgroundAlpha(int alpha)
{
    if (alpha < 0)
        alpha = 0;
    if (alpha > 255)
        alpha = 255;
    if (m_bgColor.alpha() == alpha)
        return;
    m_bgColor.setAlpha(alpha);
    update();
}

void TransparentScrollArea::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), m_bgColor);
}
