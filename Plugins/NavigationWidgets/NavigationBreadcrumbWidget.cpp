#include "NavigationBreadcrumbWidget.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "NavigationTreeParser.h"

#include <QVariant>
#include <QTimer>
#include <QScrollBar>
#include <QDynamicPropertyChangeEvent>
#include <memory>

static constexpr auto PROP_NODE = "navNode";

NavigationBreadcrumbWidget::NavigationBreadcrumbWidget(QWidget* parent) :
    QWidget(parent),
    m_isInitialized(false),
    m_tree(nullptr),
    m_scrollArea(new QScrollArea(this)),
    m_container(new QWidget(this)),
    m_layout(new QHBoxLayout),
    m_nodeFontSize(12),
    m_treeDef()
{
    initialize();
    rebuild();
}

NavigationBreadcrumbWidget::NavigationBreadcrumbWidget(NavigationTree* tree, QWidget* parent) :
    QWidget(parent),
    m_isInitialized(false),
    m_tree(nullptr),
    m_nodeFontSize(12),
    m_scrollArea(new QScrollArea(this)),
    m_container(new QWidget(this)),
    m_layout(new QHBoxLayout),
    m_treeDef()
{
    initialize();
    setTree(tree);
    rebuild();
}

void NavigationBreadcrumbWidget::initialize()
{
    if (!m_isInitialized)
    {
        /* scroll area */
        m_scrollArea->setWidgetResizable(true);
        m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_scrollArea->setFrameShape(QFrame::NoFrame);

        /* container inside scrollArea */
        m_container->setLayout(m_layout);
        m_layout->setContentsMargins(0, 0, 0, 0);
        m_layout->setSpacing(0);
        m_scrollArea->setWidget(m_container);

        /* outer layout */
        auto* outer = new QHBoxLayout(this);
        outer->setContentsMargins(0, 0, 0, 0);
        outer->addWidget(m_scrollArea);

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_isInitialized = true;
    }
}

bool NavigationBreadcrumbWidget::event(QEvent* e)
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

NavigationTree* NavigationBreadcrumbWidget::tree() const
{
    return m_tree;
}

void NavigationBreadcrumbWidget::setTree(NavigationTree* tree)
{
    if (tree == m_tree)
        return;

    if (m_tree)
        disconnect(m_tree, &NavigationTree::currentNodeChanged, this, &NavigationBreadcrumbWidget::rebuild);

    m_tree = tree;
    if (m_tree)
    {
        connect(m_tree, &NavigationTree::currentNodeChanged, this, &NavigationBreadcrumbWidget::rebuild, Qt::UniqueConnection);
    }
    rebuild();
}

int NavigationBreadcrumbWidget::nodeFontSize() const
{
    return m_nodeFontSize;
}

void NavigationBreadcrumbWidget::setNodeFontSize(int size)
{
    if (size != m_nodeFontSize)
    {
        m_nodeFontSize = size;
        rebuild();
    }
}

void NavigationBreadcrumbWidget::setTreeDef(const QString& def)
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
        qWarning() << "NavigationBreadcrumbWidget: treeDef invalid:" << err;
    }
}


QPushButton* NavigationBreadcrumbWidget::makeButton(const QString& txt, QWidget* parent, bool enabled)
{
    auto* b = new QPushButton(parent);
    b->setFont(QFont(b->font().family(), m_nodeFontSize, QFont::Normal));
    b->setEnabled(enabled);
    b->setText(txt);
    b->setFlat(true);
    b->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    return b;
}

QLabel* NavigationBreadcrumbWidget::makeLabel(const QString& txt, QWidget* parent)
{
    auto* l = new QLabel(parent);
    l->setFont(QFont(l->font().family(), m_nodeFontSize, QFont::Bold));
    l->setText(txt);
    l->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    l->setContentsMargins(8, 0, 8, 0);         // petit espace autour du chevron
    return l;
}

QLabel* NavigationBreadcrumbWidget::makeSeparator(QWidget* parent)
{
    auto* l = new QLabel(">", parent);
    l->setFont(QFont(l->font().family(), m_nodeFontSize, QFont::Normal));
    l->setContentsMargins(4, 0, 4, 0);         // petit espace autour du chevron
    return l;
}

void NavigationBreadcrumbWidget::rebuild()
{
    /* supprime tout (widgets + items de layout) */
    while (auto* item = m_layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    if (!m_tree)
        return;

    NavigationNode* cur = m_tree->currentNode();
    if (!cur)
        return;

    const QList<const NavigationNode*> segs = cur->pathNodes();    // Racine -> Courant

    for (int i = 0; i < segs.size(); ++i) {
        const NavigationNode* seg = segs.at(i);

        if (i != segs.size() - 1) {            // ancêtre => bouton cliquable
            auto* btn = makeButton(seg->name(), this, seg->isEnabled());
            btn->setProperty(PROP_NODE, QVariant::fromValue<void*>(const_cast<NavigationNode*>(seg)));
            connect(btn, &QPushButton::clicked, this, &NavigationBreadcrumbWidget::onButtonClicked);
            connect(seg, &NavigationNode::enabledChanged, btn, &QPushButton::setEnabled);
            m_layout->addWidget(btn);
        }
        else {                               // dernier segment = courant
            //m_layout->addWidget(makeButton(seg->name(), this, false));
            m_layout->addWidget(makeLabel(seg->name(), this));
        }

        if (i != segs.size() - 1)
            m_layout->addWidget(makeSeparator(this));
    }
    m_layout->addStretch(); // pousse tout à gauche

    /* s'assurer que la fin du chemin est visible quand on plonge plus profond */
    QTimer::singleShot(0, m_scrollArea, [sa = m_scrollArea] {
        sa->horizontalScrollBar()->setValue(sa->horizontalScrollBar()->maximum());
    });
}

void NavigationBreadcrumbWidget::onButtonClicked()
{
    auto* btn = qobject_cast<QPushButton*>(sender());
    auto* node = static_cast<NavigationNode*>(btn->property(PROP_NODE).value<void*>());
    if (node)
        m_tree->setCurrentNode(node);
}
