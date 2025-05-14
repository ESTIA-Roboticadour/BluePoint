#include "NavigationLayoutWidget.h"
#include "NavigationNode.h"

#include <QSizePolicy>
#include <QString>
#include <QVariant>
#include <QDynamicPropertyChangeEvent>
#include <memory>

NavigationLayoutWidget::NavigationLayoutWidget(QWidget* parent) :
    QWidget(parent),
    m_logo(new QLabel(this)),
    m_sidebar(new TogglePanel(this)),
    m_branch(new NavigationBranchWidget(m_sidebar)),   // parent = sidebar (content)
    m_breadcrumb(new NavigationBreadcrumbWidget(this)),
    m_central(new QWidget(this)),
    m_main(new QVBoxLayout(this)),
    m_topBar(new QHBoxLayout),
    m_mainArea(new QHBoxLayout),
    m_treeDef()
{
    /* ─── Logo ─── */
    m_logo->setScaledContents(true);
    m_logo->setMaximumSize(128, 128);
    m_logo->setMinimumSize(0,0);
    m_logo->setAlignment(Qt::AlignCenter);
    m_logo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    /* ─── Sidebar : on place la branche à l’intérieur du TogglePanel ─── */
    m_branch->setFixedWidth(200);
    m_sidebar->setButtonText("≡");                      // bouton hamburger
    m_sidebar->setContentWidget(m_branch);              // ≡ → branche

    /* ─── Central & layout ─── */
    m_central->setObjectName("CentralPlaceholder");
    m_central->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_topBar->addWidget(m_logo);
    m_topBar->addWidget(m_breadcrumb, /*stretch=*/1);

    m_mainArea->addWidget(m_sidebar);
    m_mainArea->addWidget(m_central, /*stretch=*/1);

    m_main->setContentsMargins(0,0,0,0);
    m_main->setSpacing(0);
    m_main->addLayout(m_topBar);
    m_main->addLayout(m_mainArea, /*stretch=*/1);
}

bool NavigationLayoutWidget::event(QEvent* e)
{
    // Designer : quand l'utilisateur modifie treeDef dans l'éditeur "..."
    if (e->type() == QEvent::DynamicPropertyChange) {
        auto *dp = static_cast<QDynamicPropertyChangeEvent*>(e);
        if (dp->propertyName() == "treeDef") {
            const QString val = property("treeDef").toString();
            setTreeDef(val);
        }
    }
    return QWidget::event(e);
}

/* ─────────────── Public API ────────────────────────────────────────── */

void NavigationLayoutWidget::setCentralWidget(QWidget* w)
{
    if (!w || w == m_central)
        return;                                 // rien à faire

    /* ─── 1. retirer l'ancien widget ─── */
    m_mainArea->removeWidget(m_central);        // QHBoxLayout hérite de QLayout
    m_central->setParent(nullptr);
    m_central->deleteLater();                   // ou conserve-le selon ton usage

    /* ─── 2. insérer le nouveau ─── */
    m_central = w;
    m_central->setParent(this);                 // le layout le ré-adopte
    m_central->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // stretch = 1 pour qu’il prenne tout l’espace libre
    m_mainArea->addWidget(m_central, /*stretch=*/1);
}

void NavigationLayoutWidget::setTree(NavigationTree* tree)
{
    m_branch->setTree(tree);
    m_breadcrumb->setTree(tree);
}

NavigationTree* NavigationLayoutWidget::getTree() const
{
    return m_branch->tree();
}

void NavigationLayoutWidget::setLogoText(const QString& txt)
{
    if (txt != logoText())
    {
        clearLogoPixmap();
        m_logo->setText(txt);
        emit logoTextChanged(txt);
    }
}

void NavigationLayoutWidget::setLogoPixmap(const QPixmap& px)
{
    m_logo->clear();
    m_logo->setPixmap(px);
    emit logoPixmapChanged(px);
}

void NavigationLayoutWidget::setLogoMaxW(int w)
{
    if (w == logoMaxW()) return;
    m_logo->setMaximumWidth(w);
}

void NavigationLayoutWidget::setLogoMaxH(int h)
{
    if (h == logoMaxH()) return;
    m_logo->setMaximumHeight(h);
}

void NavigationLayoutWidget::clearLogoPixmap()
{
    m_logo->clear();
    emit logoPixmapChanged(m_logo->pixmap());
}

void NavigationLayoutWidget::setTreeDef(const QString& def)
{
    if (def == m_treeDef) {
        return;
    }

    m_treeDef = def.trimmed();
    setProperty("treeDef", m_treeDef);   // maintient la valeur dynamique à jour

    if (m_treeDef.isEmpty()) {
        return;
    }

    std::unique_ptr<NavigationTree> t;
    QString err;

    t = m_treeDef.startsWith('{') ?
            NavigationTreeParser::fromJson(m_treeDef, &err) : // JSON inline
            NavigationTreeParser::fromFile(m_treeDef, &err);  // chemin / ressource

    if (t) {
        setTree(t.release());
    }
    else {
        qWarning() << "NavigationLayoutWidget: treeDef invalid:" << err;
    }
}
