#ifndef APPLAYOUTWIDGET_H
#define APPLAYOUTWIDGET_H

#include "AppLayout_global.h"

#include <QWidget>
#include <QLabel>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPointer>
#include <QColor>
#include <QPixmap>

#include "LayeredWidget.h"
#include "LogoWidget.h"
#include "LogWidget.h"
#include "TogglePanel.h"
#include "NavigationBranchWidget.h"
#include "NavigationBreadcrumbWidget.h"
#include "NavigationTree.h"
#include "NavigationTreeParser.h"

/* ------------------------------------------------------------------ */
/* AppLayoutWidget : navigation + background + logs                   */
/* ------------------------------------------------------------------ */
class APPLAYOUT_API AppLayoutWidget : public QWidget
{
    Q_OBJECT

    /* --- Propriétés Designer -------------------------------------- */
    Q_PROPERTY(QPixmap logoPixmap      READ logoPixmap      WRITE setLogoPixmap)
    Q_PROPERTY(int     logoWidth       READ logoWidth       WRITE setLogoWidth )
    Q_PROPERTY(int     logoHeight      READ logoHeight      WRITE setLogoHeight)

    Q_PROPERTY(int sidebarWidth        READ sidebarWidth    WRITE setSidebarWidth    DESIGNABLE true)
    Q_PROPERTY(int sidebarItemHeight   READ sidebarItemH    WRITE setSidebarItemH    DESIGNABLE true)
    Q_PROPERTY(int sidebarItemFontSize READ sidebarItemFS   WRITE setSidebarItemFS   DESIGNABLE true)
    Q_PROPERTY(int navbarFontSize      READ navbarFontSize  WRITE setNavbarFontSize  DESIGNABLE true)

    Q_PROPERTY(QPixmap backgroundLogo       READ backgroundLogo       WRITE setBackgroundLogo    )
    Q_PROPERTY(int     backgroundLogoWidth  READ backgroundLogoWidth  WRITE setBackgroundLogoWidth )
    Q_PROPERTY(int     backgroundLogoHeight READ backgroundLogoHeight WRITE setBackgroundLogoHeight)

    Q_PROPERTY(qreal  backgroundOpacity READ backgroundOpacity WRITE setBackgroundOpacity DESIGNABLE true)
    Q_PROPERTY(QColor filterColor       READ filterColor       WRITE setFilterColor       DESIGNABLE true)
    Q_PROPERTY(qreal  filterOpacity     READ filterOpacity     WRITE setFilterOpacity     DESIGNABLE true)

    Q_PROPERTY(bool showLogs READ showLogs WRITE setShowLogs DESIGNABLE true)
    Q_PROPERTY(QColor debugColor    READ debugColor    WRITE setDebugColor    DESIGNABLE true)
    Q_PROPERTY(QColor infoColor     READ infoColor     WRITE setInfoColor     DESIGNABLE true)
    Q_PROPERTY(QColor warningColor  READ warningColor  WRITE setWarningColor  DESIGNABLE true)
    Q_PROPERTY(QColor criticalColor READ criticalColor WRITE setCriticalColor DESIGNABLE true)
    Q_PROPERTY(QColor fatalColor    READ fatalColor    WRITE setFatalColor    DESIGNABLE true)

public:
    explicit AppLayoutWidget(QWidget* parent = nullptr);
    ~AppLayoutWidget() override = default;

    /* -------- getters simples ------------------------------------- */
    // logo
    QPixmap logoPixmap()  const { return m_logo->logoPixmap(); }
    int     logoWidth()   const { return m_logo->logoWidth(); }
    int     logoHeight()  const { return m_logo->logoHeight(); }

    // sidebar / navbar
    int sidebarWidth()      const { return m_branch->width(); }
    int sidebarItemH()      const { return m_branch->nodeHeight(); }
    int sidebarItemFS()     const { return m_branch->nodeFontSize(); }
    int navbarFontSize()    const { return m_breadcrumb->nodeFontSize(); }

    // layered background
    QPixmap backgroundLogo()        const { return m_bgLogo->logoPixmap(); }
    int     backgroundLogoWidth()   const { return m_bgLogo->logoWidth(); }
    int     backgroundLogoHeight()  const { return m_bgLogo->logoHeight(); }

    qreal  backgroundOpacity() const { return m_layered->backgroundOpacity(); }
    QColor filterColor()        const { return m_layered->filterColor(); }
    qreal  filterOpacity()      const { return m_layered->filterOpacity(); }

    bool showLogs() const { return m_splitter->sizes().at(1) > 0; }
    QColor debugColor()    const;
    QColor infoColor()     const;
    QColor warningColor()  const;
    QColor criticalColor() const;
    QColor fatalColor()    const;

    // tree
    NavigationTree* getTree() const { return m_branch->tree(); }
    QString treeDef() const { return m_treeDef; }

public slots:
    /* --- Logo ----------------------------------------------------- */
    void setLogoPixmap(const QPixmap& px);
    void setLogoWidth(int w);
    void setLogoHeight(int h);

    /* --- Sidebar / navbar ---------------------------------------- */
    void setSidebarWidth(int w)            { m_branch->setFixedWidth(w);              }
    void setSidebarItemH(int h)            { m_branch->setNodeHeight(h);              }
    void setSidebarItemFS(int fs)          { m_branch->setNodeFontSize(fs);           }
    void setNavbarFontSize(int fs)         { m_breadcrumb->setNodeFontSize(fs);       }

    /* --- Background / filtre ------------------------------------- */
    void setBackgroundLogo(const QPixmap& px);
    void setBackgroundLogoWidth(int w);
    void setBackgroundLogoHeight(int h);

    void setBackgroundOpacity(qreal a)     { m_layered->setBackgroundOpacity(a);      }
    void setFilterColor(const QColor& c)   { m_layered->setFilterColor(c);            }
    void setFilter(const QColor& c, qreal a) { m_layered->setFilter(c, a);            }
    void setFilterOpacity(qreal a)         { m_layered->setFilterOpacity(a);          }
    void clearFilter()                     { m_layered->clearFilter();                }

    void hideBackground() const            { m_bgLogo->hide(); }
    void showBackground() const            { m_bgLogo->show(); }

    /* --- Logs visibility ----------------------------------------- */
    void setShowLogs(bool on);
    void setDebugColor   (const QColor&);
    void setInfoColor    (const QColor&);
    void setWarningColor (const QColor&);
    void setCriticalColor(const QColor&);
    void setFatalColor   (const QColor&);

    /* --- Central user area --------------------------------------- */
    void setCentralWidget(QWidget* w, bool deleteOld = true)   { m_layered->setForegroundWidget(w, deleteOld); }
    void clearCentralWidget(bool deleteOld = true)             { m_layered->setForegroundWidget(nullptr, deleteOld); }

    /* --- Navigation tree ----------------------------------------- */
    void setTree(NavigationTree* t);
    void setTreeDef(const QString& def);

signals:
    void logoSizeChanged();

protected:
    bool event(QEvent* e) override;          // gestion live de treeDef en Designer

private:
    /* ---- sous-composants ---------------------------------------- */
    LogoWidget*                 m_logo   { nullptr };
    TogglePanel*                m_sidebar{ nullptr };
    NavigationBranchWidget*     m_branch { nullptr };
    NavigationBreadcrumbWidget* m_breadcrumb{ nullptr };

    LayeredWidget*              m_layered{ nullptr };
    LogoWidget*                 m_bgLogo { nullptr };   // logo arrière-plan
    LogWidget*                  m_logs   { nullptr };
    QSplitter*                  m_splitter{ nullptr };

    /* ---- layouts ------------------------------------------------- */
    QVBoxLayout* m_main   { nullptr };
    QHBoxLayout* m_topBar { nullptr };
    QHBoxLayout* m_mainArea{ nullptr };

    /* ---- autres -------------------------------------------------- */
    QString m_treeDef;
};

#endif // APPLAYOUTWIDGET_H
