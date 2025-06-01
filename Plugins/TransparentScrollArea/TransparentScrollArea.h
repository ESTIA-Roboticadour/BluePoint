#ifndef TRANSPARENTSCROLLAREA_H
#define TRANSPARENTSCROLLAREA_H

#include "TransparentScrollArea_global.h"

#include <QWidget>
#include <QScrollArea>
#include <QColor>
#include <QVBoxLayout>

class TRANSPARENTSCROLLAREA_API TransparentScrollArea : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(int backgroundAlpha READ backgroundAlpha WRITE setBackgroundAlpha)

public:
    explicit TransparentScrollArea(QWidget* parent = nullptr);

    /** Returns the internal scroll area so that the user can set its widget() or tweak options. */
    QScrollArea* scrollArea() const { return m_scrollArea; }

    QColor backgroundColor() const { return m_bgColor; }
    int    backgroundAlpha() const { return m_bgColor.alpha(); }

public slots:
    void setBackgroundColor(const QColor& color);
    void setBackgroundAlpha(int alpha);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QScrollArea* m_scrollArea;
    QColor       m_bgColor;
};

#endif // TRANSPARENTSCROLLAREA_H
