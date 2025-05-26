#ifndef LAYEREDWIDGET_H
#define LAYEREDWIDGET_H

#include "LayeredWidget_global.h"

#include <QWidget>
#include <QPointer>
#include <QColor>
#include <algorithm>   // std::clamp

class LAYEREDWIDGET_API LayeredWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal  backgroundOpacity READ backgroundOpacity WRITE setBackgroundOpacity NOTIFY backgroundOpacityChanged)
    Q_PROPERTY(QColor filterColor       READ filterColor       WRITE setFilterColor       NOTIFY filterColorChanged)
    Q_PROPERTY(qreal  filterOpacity     READ filterOpacity     WRITE setFilterOpacity     NOTIFY filterOpacityChanged)

public:
    explicit LayeredWidget(QWidget* parent = nullptr);

    /* --- mise en place / modification ----------------------------- */
    void setBackgroundWidget(QWidget* w, bool deleteOld = true);
    void setForegroundWidget(QWidget* w, bool deleteOld = true);
    void swapLayers();                                   // échange back <-> front

    /* --- opacité background --------------------------------------- */
    qreal backgroundOpacity() const;

    /* --- filtre couleur / alpha ----------------------------------- */
    QColor filterColor()   const;
    qreal  filterOpacity() const;
    void   clearFilter();                                // supprime le filtre

    /* API d’origine (couleur + alpha en même temps) */
    void setFilter(const QColor& c, qreal alpha);

public slots:
    void setBackgroundOpacity(qreal alpha);             // 0..1
    void setFilterColor(const QColor& c);              // conserve l’opacité courante
    void setFilterOpacity(qreal alpha);                // conserve la couleur courante

signals:
    void backgroundOpacityChanged(qreal);
    void filterColorChanged(const QColor&);
    void filterOpacityChanged(qreal);

protected:
    void resizeEvent(QResizeEvent* e) override;

private:
    void applyOpacity();
    void updateGeometryAndStacking();
    void ensureFilterExists();

    QPointer<QWidget> m_back;
    QPointer<QWidget> m_front;
    QWidget*          m_filter { nullptr };
    qreal             m_backOpacity { 0.5 };

    QColor  m_filterColor { Qt::black };
    qreal   m_filterAlpha { 0.5 };
};

#endif // LAYEREDWIDGET_H
