#include "NavigationBreadcrumbWidget.h"
#include "NavigationTree.h"
#include "NavigationNode.h"

#include <QVariant>
#include <QTimer>
#include <QScrollBar>

static constexpr auto PROP_NODE = "navNode";

NavigationBreadcrumbWidget::NavigationBreadcrumbWidget(QWidget* parent) :
    QWidget(parent),
    m_isInitialized(false),
    m_tree(nullptr),
    m_scrollArea(new QScrollArea(this)),
    m_container(new QWidget(this)),
    m_layout(new QHBoxLayout),
    m_nodeFontSize(12)
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
    m_layout(new QHBoxLayout)
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
        connect(m_tree, &NavigationTree::currentNodeChanged, this, &NavigationBreadcrumbWidget::rebuild);
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
QPushButton* NavigationBreadcrumbWidget::makeButton(const QString& txt, QWidget* parent)
{
    auto* b = new QPushButton(parent);
    b->setFont(QFont(b->font().family(), m_nodeFontSize, QFont::Normal));
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
    l->setContentsMargins(4, 0, 4, 0);         // petit espace autour du chevron
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

    if (m_tree == nullptr)
        return;

    const QList<const NavigationNode*> segs = m_tree->currentNode()->pathNodes();    // Racine -> Courant

    for (int i = 0; i < segs.size(); ++i) {
        const NavigationNode* seg = segs.at(i);

        if (i != segs.size() - 1) {            // ancêtre => bouton cliquable
            auto* btn = makeButton(seg->name(), this);
            btn->setProperty(PROP_NODE, QVariant::fromValue<void*>(const_cast<NavigationNode*>(seg)));
            connect(btn, &QPushButton::clicked, this, &NavigationBreadcrumbWidget::onButtonClicked);
            m_layout->addWidget(btn);
        }
        else {                               // dernier segment = courant
            m_layout->addWidget(makeLabel(seg->name(), this));
        }

        if (i != segs.size() - 1)
            m_layout->addWidget(makeSeparator(this));
    }
    m_layout->addStretch();                    // pousse tout à gauche

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
