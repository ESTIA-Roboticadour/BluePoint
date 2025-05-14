#include "NavigationBranchWidget.h"
#include "NavigationTreeParser.h"

#include <QVBoxLayout>
#include <QVector>
#include <QPushButton>
#include <QFrame>
#include <QDynamicPropertyChangeEvent>

static constexpr auto BTN_PROP_NODE = "navNode";

NavigationBranchWidget::NavigationBranchWidget(QWidget* parent) :
    QWidget(parent),
    m_isInitialized(false),
    m_tree(nullptr),
    m_scroll(new QScrollArea(this)),
    m_container(new QWidget()),
    m_layout(new QVBoxLayout()),
    m_nodeHeight(40),
    m_nodeFontSize(12),
    m_treeDef()
{
    initialize();
    rebuild();
}

NavigationBranchWidget::NavigationBranchWidget(NavigationTree* tree, QWidget* parent) :
    QWidget(parent),
    m_tree(nullptr),
    m_scroll(new QScrollArea(this)),
    m_container(new QWidget()),
    m_layout(new QVBoxLayout()),
    m_nodeHeight(40),
    m_nodeFontSize(12),
    m_treeDef()
{
    initialize();
    setTree(tree);
    rebuild();
}

void NavigationBranchWidget::initialize()
{
    if (!m_isInitialized)
    {
        m_container->setLayout(m_layout);
        m_layout->setContentsMargins(0, 0, 0, 0);
        m_layout->setSpacing(0);

        m_scroll->setWidgetResizable(true);
        m_scroll->setWidget(m_container);

        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(m_scroll);

        m_isInitialized = true;
    }
}

bool NavigationBranchWidget::event(QEvent* e)
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

NavigationTree* NavigationBranchWidget::tree() const
{
    return m_tree;
}

void NavigationBranchWidget::setTree(NavigationTree* tree)
{
    if (tree == m_tree)
        return;

    if (m_tree)
        disconnect(m_tree, &NavigationTree::currentNodeChanged, this, &NavigationBranchWidget::rebuild);

    m_tree = tree;
    if (m_tree)
        connect(m_tree, &NavigationTree::currentNodeChanged, this, &NavigationBranchWidget::rebuild, Qt::UniqueConnection);

    rebuild();
}

QLabel* NavigationBranchWidget::makeLabel(const QString& text, QWidget* parent)
{
    auto* l = new QLabel(parent);
    l->setFont(QFont(l->font().family(), m_nodeFontSize, QFont::Bold));
    l->setText(text);
    l->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    l->setMinimumHeight(m_nodeHeight);
    return l;
}

QPushButton* NavigationBranchWidget::makeButton(const QString& text, QWidget* parent, bool enabled)
{
    auto* b = new QPushButton(parent);
    b->setFont(QFont(b->font().family(), m_nodeFontSize, QFont::Normal));
    b->setEnabled(enabled);
    b->setText(text);
    b->setFlat(true);
    b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    b->setMinimumHeight(m_nodeHeight);
    return b;
}

QFrame* NavigationBranchWidget::makeSeparator(QWidget* parent)
{
    auto* sep = new QFrame(parent);
    sep->setFrameShape(QFrame::HLine);
    sep->setFrameShadow(QFrame::Sunken);
    return sep;
}

void NavigationBranchWidget::rebuild()
{
    // ---------- vide le layout ----------
    while (auto* item = m_layout->takeAt(0))
    {
        delete item->widget();
        delete item;
    }

    if (!m_tree)
    {
        return;
    }

    NavigationNode* cur = m_tree->currentNode();

    if (!cur)
    {
        return;
    }

    // ---------- 1. Label courant ----------
    m_layout->addWidget(makeLabel(cur->name(), m_container));
    m_layout->addWidget(makeSeparator(m_container));

    // ---------- 2. Bouton Parent ----------
    if (cur->hasParent())
    {
        auto* upBtn = makeButton(cur->parentNode()->name(), m_container, cur->isEnabled());
        upBtn->setProperty(BTN_PROP_NODE, QVariant::fromValue<void*>(cur->parentNode()));
        connect(upBtn, &QPushButton::clicked, this, &NavigationBranchWidget::onButtonClicked);
        connect(cur, &NavigationNode::enabledChanged, upBtn, &QPushButton::setEnabled);
        m_layout->addWidget(upBtn);
        m_layout->addWidget(makeSeparator(m_container));
    }

    if (cur->hasChildren())
    {
        // ---------- 3. Enfants ----------
        const auto& nodes = cur->children();
        for (NavigationNode* n : nodes)
        {
            auto* btn = makeButton(n->name(), m_container, n->isEnabled());
            btn->setProperty(BTN_PROP_NODE, QVariant::fromValue<void*>(n));
            btn->setChecked(n->isSelected());   // reflète la sélection
            connect(btn, &QPushButton::clicked, this, &NavigationBranchWidget::onButtonClicked);
            connect(n, &NavigationNode::enabledChanged, btn, &QPushButton::setEnabled);
            m_layout->addWidget(btn);
        }
    }
    else
    {
        // ---------- 3. Frères ----------
        const auto& nodes = cur->parentNode()->children();
        for (NavigationNode* n : nodes)
        {
            auto* btn = makeButton(n->name(), m_container, n->isEnabled());
            btn->setProperty(BTN_PROP_NODE, QVariant::fromValue<void*>(n));
            btn->setChecked(n->isSelected());   // reflète la sélection
            connect(btn, &QPushButton::clicked, this, &NavigationBranchWidget::onButtonClicked);
            connect(n, &NavigationNode::enabledChanged, btn, &QPushButton::setEnabled);
            m_layout->addWidget(btn);
        }
    }
    m_layout->addStretch(); // pousse tout vers le haut
}

int NavigationBranchWidget::nodeHeight() const
{
    return m_nodeHeight;
}

void NavigationBranchWidget::setNodeHeight(int height)
{
    if (height != m_nodeHeight)
    {
        m_nodeHeight = height;
        rebuild();
    }
}

int NavigationBranchWidget::nodeFontSize() const
{
    return m_nodeFontSize;
}

void NavigationBranchWidget::setNodeFontSize(int size)
{
    if (size != m_nodeFontSize)
    {
        m_nodeFontSize = size;
        rebuild();
    }
}

void NavigationBranchWidget::setTreeDef(const QString& def)
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

        qWarning() << "NavigationBranchWidget: treeDef invalid:" << err;
    }
}

void NavigationBranchWidget::onButtonClicked()
{
    auto* btn = qobject_cast<QPushButton*>(sender());
    auto* node = static_cast<NavigationNode*>(btn->property(BTN_PROP_NODE).value<void*>());
    if (node)
        m_tree->setCurrentNode(node);
}
