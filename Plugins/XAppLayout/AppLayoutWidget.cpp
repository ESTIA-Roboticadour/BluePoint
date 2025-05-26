#include "AppLayoutWidget.h"

#include <QDynamicPropertyChangeEvent>
#include <QTimer>
#include <memory>

/* ------------------------------------------------------------------ */
/* helper : pour collapse logs = splitter                             */
/* ------------------------------------------------------------------ */
namespace {
inline int total(const QList<int>& v)
{
    int s = 0; for (int x : v) s += x; return s;
}
}

/* ------------------------------------------------------------------ */
/* ctor                                                               */
/* ------------------------------------------------------------------ */
AppLayoutWidget::AppLayoutWidget(QWidget* parent) :
    QWidget(parent),
    m_logo      (new LogoWidget(this)),
    m_sidebar   (new TogglePanel(this)),
    m_branch    (new NavigationBranchWidget(m_sidebar)),
    m_breadcrumb(new NavigationBreadcrumbWidget(this)),
    m_layered   (new LayeredWidget(this)),
    m_bgLogo    (new LogoWidget()),
    m_logs      (new LogWidget(this)),
    m_splitter  (new QSplitter(Qt::Vertical, this)),
    m_main      (new QVBoxLayout(this)),
    m_topBar    (new QHBoxLayout),
    m_mainArea  (new QHBoxLayout)
{
    /* --- logo barre du haut -------------------------------------- */
    m_logo->setLogoWidth(64);
    m_logo->setLogoHeight(64);

    /* --- sidebar + branche --------------------------------------- */
    m_branch->setFixedWidth(200);
    m_sidebar->setButtonText("≡");
    m_sidebar->setContentWidget(m_branch);

    /* --- layered background : logo + central --------------------- */
    m_layered->setBackgroundWidget(m_bgLogo);

    /* --- splitter (layered / logs) -------------------------------- */
    m_splitter->addWidget(m_layered);
    m_splitter->addWidget(m_logs);
    m_splitter->setCollapsible(1, true);
    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 1);

    /* --- layout --------------------------------------------------- */
    m_topBar->addWidget(m_logo);
    m_topBar->addWidget(m_breadcrumb, 1);

    m_mainArea->addWidget(m_sidebar);
    m_mainArea->addWidget(m_splitter, 1);

    m_main->setContentsMargins(0,0,0,0);
    m_main->setSpacing(0);
    m_main->addLayout(m_topBar);
    m_main->addLayout(m_mainArea, 1);

    setLayout(m_main);

    QTimer::singleShot(0, this, [this] {
        const int h = m_splitter->height();
        if (h > 0)
            m_splitter->setSizes({ int(h*0.8), int(h*0.2) });
    });
}

/* ------------------------------------------------------------------ */
/* LOGO                                                               */
/* ------------------------------------------------------------------ */

void AppLayoutWidget::setLogoPixmap(const QPixmap& px) { m_logo->setLogoPixmap(px); }
void AppLayoutWidget::setLogoWidth(int w)  { m_logo->setLogoWidth(w); }
void AppLayoutWidget::setLogoHeight(int h) { m_logo->setLogoHeight(h); }

void AppLayoutWidget::setBackgroundLogo(const QPixmap& px) { m_bgLogo->setLogoPixmap(px); }
void AppLayoutWidget::setBackgroundLogoWidth(int w) { m_bgLogo->setLogoWidth(w); }
void AppLayoutWidget::setBackgroundLogoHeight(int h) { m_bgLogo->setLogoHeight(h); }

/* ------------------------------------------------------------------ */
/* LOGS visibility                                                    */
/* ------------------------------------------------------------------ */
void AppLayoutWidget::setShowLogs(bool on)
{
    QList<int> sz = m_splitter->sizes();
    if (on && sz.at(1) == 0) {
        sz[1] = std::max(100, total(sz) / 5);   // 20 %
        sz[0] = total(sz) - sz[1];
        m_splitter->setSizes(sz);
    }
    else if (!on && sz.at(1) > 0) {
        sz[0] = total(sz);
        sz[1] = 0;
        m_splitter->setSizes(sz);
    }
}

void AppLayoutWidget::setDebugColor   (const QColor& c) { m_logs->setDebugColor(c); }
void AppLayoutWidget::setInfoColor    (const QColor& c) { m_logs->setInfoColor(c); }
void AppLayoutWidget::setWarningColor (const QColor& c) { m_logs->setWarningColor(c); }
void AppLayoutWidget::setCriticalColor(const QColor& c) { m_logs->setCriticalColor(c); }
void AppLayoutWidget::setFatalColor   (const QColor& c) { m_logs->setFatalColor(c); }

QColor AppLayoutWidget::debugColor()    const { return m_logs->debugColor(); }
QColor AppLayoutWidget::infoColor()     const { return m_logs->infoColor(); }
QColor AppLayoutWidget::warningColor()  const { return m_logs->warningColor(); }
QColor AppLayoutWidget::criticalColor() const { return m_logs->criticalColor(); }
QColor AppLayoutWidget::fatalColor()    const { return m_logs->fatalColor(); }

/* ------------------------------------------------------------------ */
/* Navigation tree                                                    */
/* ------------------------------------------------------------------ */
void AppLayoutWidget::setTree(NavigationTree* t)
{
    m_branch->setTree(t);
    m_breadcrumb->setTree(t);
}

void AppLayoutWidget::setTreeDef(const QString& def)
{
    const QString trimmed = def.trimmed();
    if (trimmed == m_treeDef) return;

    m_treeDef = trimmed;
    setProperty("treeDef", m_treeDef);   // pour Designer
    if (m_treeDef.isEmpty()) return;

    QString err;
    std::unique_ptr<NavigationTree> t = m_treeDef.startsWith('{') ?
                                            NavigationTreeParser::fromJson(m_treeDef, &err) :
                                            NavigationTreeParser::fromFile(m_treeDef, &err);

    if (!t) {
        qWarning() << "AppLayoutWidget: treeDef invalid:" << err;
        return;
    }
    setTree(t.release());
}

/* ------------------------------------------------------------------ */
/* event : mise à jour live de treeDef dans Designer                  */
/* ------------------------------------------------------------------ */
bool AppLayoutWidget::event(QEvent* e)
{
    bool r = QWidget::event(e);
    if (e->type() == QEvent::DynamicPropertyChange) {
        auto* dp = static_cast<QDynamicPropertyChangeEvent*>(e);
        if (dp->propertyName() == "treeDef")
            setTreeDef(property("treeDef").toString());
    }
    return r;
}
