#ifndef TOGGLEPANEL_H
#define TOGGLEPANEL_H

#include "TogglePanel_global.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QIcon>
#include <QSizePolicy>
#include <QEasingCurve>
#include <limits>

class TOGGLEPANEL_API TogglePanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText)
    Q_PROPERTY(QIcon   buttonIcon READ buttonIcon WRITE setButtonIcon)
    Q_PROPERTY(QSize   buttonSize READ buttonSize WRITE setButtonSize)
    Q_PROPERTY(bool    buttonFlat READ buttonFlat WRITE setButtonFlat)
    Q_PROPERTY(Qt::Alignment buttonHAlignment READ buttonHAlignment WRITE setButtonHAlignment)

public:
    explicit TogglePanel(QWidget* parent = nullptr);

    // Contenu embarqué
    void    setContentWidget(QWidget* w);
    QWidget* contentWidget() const { return m_content; }

    // Propriétés du bouton
    QString buttonText()  const { return m_button->text(); }
    void    setButtonText(const QString& text) { m_button->setText(text); }

    QIcon   buttonIcon()  const { return m_button->icon(); }
    void    setButtonIcon(const QIcon& icon) { m_button->setIcon(icon); }

    QSize   buttonSize()  const { return m_button->size(); }
    void    setButtonSize(const QSize& sz);

    bool    buttonFlat() const;
    void    setButtonFlat(const bool flat);

    Qt::Alignment buttonHAlignment() const;
    void setButtonHAlignment(Qt::Alignment alignment);

public slots:
    void open();
    void close();

signals:
    void opened();
    void closed();

protected:
    void childEvent(QChildEvent* e) override;

private slots:
    void toggle();

private:
    int  collapsedWidth() const;
    int  expandedWidth()  const;
    void animate(int start, int end);

    QPushButton*        m_button;
    QWidget*            m_content;
    QVBoxLayout*        m_layout;
    QPropertyAnimation* m_anim;
    bool                m_open;
    bool                m_setting; // pour éviter recursion childEvent
    Qt::Alignment       m_buttonHAlign;
};

#endif // TOGGLEPANEL_H
