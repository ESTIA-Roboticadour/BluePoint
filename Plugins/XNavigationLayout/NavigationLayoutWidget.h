#ifndef NAVIGATIONLAYOUTWIDGET_H
#define NAVIGATIONLAYOUTWIDGET_H

#include "NavigationLayout_global.h"
#include "TogglePanel.h"
#include "NavigationTree.h"
#include "NavigationBranchWidget.h"
#include "NavigationBreadcrumbWidget.h"
#include "NavigationTreeParser.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QEvent> // pour QEvent, QEvent::DynamicPropertyChange

class NAVIGATIONLAYOUT_API NavigationLayoutWidget : public QWidget
{
    Q_OBJECT
    /* ─── Propriétés Designer pour le logo ─────────────────────────── */
    Q_PROPERTY(QString logoText   READ logoText   WRITE setLogoText   NOTIFY logoTextChanged)
    Q_PROPERTY(QPixmap logoPixmap READ logoPixmap WRITE setLogoPixmap NOTIFY logoPixmapChanged)
    Q_PROPERTY(int     logoMaxW   READ logoMaxW   WRITE setLogoMaxW  )
    Q_PROPERTY(int     logoMaxH   READ logoMaxH   WRITE setLogoMaxH  )

    Q_PROPERTY(int sidebarWidth        READ sidebarWidth        WRITE setSidebarWidth       )
    Q_PROPERTY(int sidebarItemHeight   READ sidebarItemHeight   WRITE setSidebarItemHeight  )
    Q_PROPERTY(int sidebarItemFontSize READ sidebarItemFontSize WRITE setSidebarItemFontSize)
    Q_PROPERTY(int navbarFontSize      READ navbarFontSize      WRITE setNavbarFontSize     )

public:
    explicit NavigationLayoutWidget(QWidget* parent = nullptr);
    ~NavigationLayoutWidget() override = default;

    /* ─── Internal components access (const)  */
    QLabel*                     logoLabel()        const { return m_logo; }
    TogglePanel*                sidebar()          const { return m_sidebar; }
    NavigationBranchWidget*     branchWidget()     const { return m_branch; }
    NavigationBreadcrumbWidget* breadcrumbWidget() const { return m_breadcrumb; }
    QWidget*                    centralWidget()    const;

    /* ─── public API — content & navigation ───────────────────────── */
    NavigationTree* getTree() const;

    /* ─── Getters ───────────────────────────── */
    QString logoText()   const { return m_logo->text(); }
    QPixmap logoPixmap() const { return m_logo->pixmap(); }
    int logoMaxW() const { return m_logo->maximumWidth(); }
    int logoMaxH() const { return m_logo->maximumHeight(); }

    int sidebarWidth() const { return m_branch->width(); }
    int sidebarItemHeight() const { return m_branch->nodeHeight(); }
    int sidebarItemFontSize() const { return m_branch->nodeFontSize(); }
    int navbarFontSize() const { return m_breadcrumb->nodeFontSize(); }

    /* ─── Public slots ───────────────────────────── */
public slots:
    void setLogoText(const QString& txt);
    void setLogoPixmap(const QPixmap& px);
    void setLogoMaxW(int w);
    void setLogoMaxH(int h);

    void setSidebarWidth(int  w) { m_branch->setFixedWidth(w); }
    void setSidebarItemHeight(int h) { m_branch->setNodeHeight(h); }
    void setSidebarItemFontSize(int s) { m_branch->setNodeFontSize(s); }
    void setNavbarFontSize(int s) { m_breadcrumb->setNodeFontSize(s); }

    void openSidebar() const { m_sidebar->open(); }
    void closeSidebar() const { m_sidebar->close(); }

    void clearLogoPixmap();

    void clearCentralWidget();
    void setCentralWidget(QWidget* w);
    void setTree(NavigationTree* tree);

protected:
    bool event(QEvent* e) override;

private:
    void setTreeDef(const QString& def);

signals:
    void logoTextChanged(const QString& logoText);
    void logoPixmapChanged(const QPixmap& logoPixmap);


    /* ─── Members ───────────────────────────────────────────────────── */
private:
    QLabel*                     m_logo;
    TogglePanel*                m_sidebar;
    NavigationBranchWidget*     m_branch;
    NavigationBreadcrumbWidget* m_breadcrumb;
    QWidget*                    m_central;
    QVBoxLayout*                m_main;     // vertical: top bar + main area
    QHBoxLayout*                m_topBar;   // logo + breadcrumb
    QHBoxLayout*                m_mainArea; // sidebar + central
    QString                     m_treeDef;
};

#endif // NAVIGATIONLAYOUTWIDGET_H
