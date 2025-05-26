#include "TogglePanel.h"

#include <QChildEvent>
#include <QtGlobal>   // QWIDGETSIZE_MAX
#include <algorithm>

TogglePanel::TogglePanel(QWidget* parent) :
    QWidget(parent),
    m_button(new QPushButton("☰", this)),
    m_content(nullptr),
    m_layout(new QVBoxLayout(this)),
    m_anim(new QPropertyAnimation(this, "maximumWidth", this)),
    m_open(false),
    m_setting(false),
    m_buttonHAlign(Qt::AlignLeft)
{
    m_button->setFixedSize(30, 30);
    connect(m_button, &QPushButton::clicked, this, &TogglePanel::toggle);

    // Layout interne
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_button, 0, Qt::AlignTop|m_buttonHAlign);
    setLayout(m_layout);

    // sizePolicy : hauteur extensible, largeur minimale
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    setMinimumWidth(collapsedWidth());
    setMaximumWidth(collapsedWidth());
    setMaximumHeight(QWIDGETSIZE_MAX);

    // Animation
    m_anim->setDuration(200);
    m_anim->setEasingCurve(QEasingCurve::InOutQuad);
}

void TogglePanel::setContentWidget(QWidget* w)
{
    if (m_setting)
        return;              // évite recursion via childEvent

    if (!w || w == m_content)
        return;

    if (m_content)
        m_content->setParent(nullptr);

    m_setting = true;

    m_content = w;
    m_content->setParent(this);
    m_content->setVisible(false);

    m_layout->insertWidget(1, m_content, 1);

    // Contraintes largeur : panneau fermé
    const int cw = collapsedWidth();
    setMinimumWidth(cw);
    setMaximumWidth(expandedWidth());
    if (!m_open)
    {
        open();
    }
    m_setting = false;
}

void TogglePanel::setButtonSize(const QSize& sz)
{
    m_button->setFixedSize(sz);
    const int cw = collapsedWidth();
    setMinimumWidth(cw);
    if (!m_open)
        setMaximumWidth(cw);
}

bool TogglePanel::buttonFlat() const
{
    return m_button->isFlat();
}

void TogglePanel::setButtonFlat(const bool flat)
{
    m_button->setFlat(flat);
}

Qt::Alignment TogglePanel::buttonHAlignment() const
{
    return m_buttonHAlign;
}

void TogglePanel::setButtonHAlignment(Qt::Alignment alignment)
{
    // On ne garde que le côté horizontal (Left, Right ou HCenter)
    const Qt::Alignment hOnly = alignment & (Qt::AlignLeft | Qt::AlignHCenter | Qt::AlignRight);

    // valeur par défaut si rien de spécifié
    const Qt::Alignment newAlign = hOnly == 0 ? Qt::AlignLeft : hOnly;

    if (newAlign != m_buttonHAlign)
    {
        m_buttonHAlign = newAlign;
        m_layout->setAlignment(m_button,  Qt::AlignTop | m_buttonHAlign);
    }
}

void TogglePanel::childEvent(QChildEvent* e)
{
    if (m_button && e->type() == QEvent::ChildAdded && !m_content) {
        if (auto w = qobject_cast<QWidget*>(e->child())) {
            if (w && w != m_button && !w->isWindow()) {
                // Reporter à la fin de l'évènement pour éviter d'interférer
                QMetaObject::invokeMethod(this, [this, w] { setContentWidget(w); }, Qt::QueuedConnection);
            }
        }
    }
    QWidget::childEvent(e);
}

void TogglePanel::open() { if (!m_open && m_content) toggle(); }
void TogglePanel::close() { if (m_open && m_content) toggle(); }

void TogglePanel::toggle()
{
    if (!m_content)
        return;

    m_open = !m_open;
    const int start = m_open ? collapsedWidth() : expandedWidth();
    const int end = m_open ? expandedWidth() : collapsedWidth();

    m_content->setVisible(true);
    animate(start, end);
}

int TogglePanel::collapsedWidth() const
{
    return m_button->size().width() + 1;
}

int TogglePanel::expandedWidth() const
{
    if (!m_content)
        return collapsedWidth();
    return std::max(collapsedWidth(), m_content->width());
}

void TogglePanel::animate(int start, int end)
{
    if (start == end) {
        if (end == collapsedWidth()) {
            if (m_content) m_content->setVisible(false);
            emit closed();
        }
        else {
            emit opened();
        }
        return;
    }

    m_anim->stop();
    m_anim->setStartValue(start);
    m_anim->setEndValue(end);

    disconnect(m_anim, nullptr, this, nullptr);
    connect(m_anim, &QPropertyAnimation::finished, this, [this, end] {
        if (end == collapsedWidth()) {
            if (m_content) m_content->setVisible(false);
            emit closed();
        }
        else {
            emit opened();
        }
        });

    m_anim->start();
}
