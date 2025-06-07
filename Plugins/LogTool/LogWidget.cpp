#include "LogWidget.h"
#include "LogDispatcher.h"

#include <QHeaderView>
#include <QMenu>
#include <QClipboard>
#include <QShortcut>
#include <QApplication>

LogWidget::LogWidget(QWidget* parent) : 
    QWidget(parent)
{
    m_view = new QTableView(this);
    m_model = new LogModel(this);

    m_view->setModel(m_model);
    m_view->setAlternatingRowColors(true);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->horizontalHeader()->setStretchLastSection(true);
    m_view->setSortingEnabled(true);

    auto* lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(m_view);

    connect(&LogDispatcher::instance(), &LogDispatcher::newEntry, this, &LogWidget::onLogAppended);

    auto* scCopy = new QShortcut(QKeySequence::Copy, m_view);
    connect(scCopy, &QShortcut::activated, this, &LogWidget::copySelectedRow);

    m_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_view, &QTableView::customContextMenuRequested, this, &LogWidget::showContextMenu);

    const int widths[] = { 80, 40, 60, 50, 120, 400 };          // Time, Lvl, Thread, Cat., File, Message
    for (int i = 0; i < LogModel::Count; ++i) {
        m_view->horizontalHeader()->resizeSection(i, widths[i]);
    }
}

/* -- nouvelles méthodes ------------------------------------------- */
QColor LogWidget::debugColor()    const { return m_model->getColor(QtDebugMsg);    }
QColor LogWidget::infoColor()     const { return m_model->getColor(QtInfoMsg);     }
QColor LogWidget::warningColor()  const { return m_model->getColor(QtWarningMsg);  }
QColor LogWidget::criticalColor() const { return m_model->getColor(QtCriticalMsg); }
QColor LogWidget::fatalColor()    const { return m_model->getColor(QtFatalMsg);    }

void LogWidget::setDebugColor   (const QColor& c) { m_model->setColor(QtDebugMsg,    c); }
void LogWidget::setInfoColor    (const QColor& c) { m_model->setColor(QtInfoMsg,     c); }
void LogWidget::setWarningColor (const QColor& c) { m_model->setColor(QtWarningMsg,  c); }
void LogWidget::setCriticalColor(const QColor& c) { m_model->setColor(QtCriticalMsg, c); }
void LogWidget::setFatalColor   (const QColor& c) { m_model->setColor(QtFatalMsg,    c); }

void LogWidget::onLogAppended(const LogEntry& entry)
{
    m_model->append(entry);
    m_view->scrollToBottom();
}

void LogWidget::copySelectedRow()
{
    const auto rows = m_view->selectionModel()->selectedRows();
    if (rows.isEmpty())
        return;
    const int row = rows.first().row();
    const QString text = m_model->data(m_model->index(row, LogModel::Message), Qt::DisplayRole).toString();
    QApplication::clipboard()->setText(text);
}

void LogWidget::showContextMenu(const QPoint& pos)
{
    const QModelIndex idx = m_view->indexAt(pos);
    const bool hasRow = idx.isValid();

    QMenu menu(this);
    QAction* copyMsg  = menu.addAction("Copy message");
    QAction* copyRow  = menu.addAction("Copy full row");
    copyMsg->setEnabled(hasRow);          // désactivé s’il n’y a pas de ligne
    copyRow->setEnabled(hasRow);

    menu.addSeparator();
    QAction* clearAll = menu.addAction("Clear log");

    QAction* chosen = menu.exec(m_view->viewport()->mapToGlobal(pos));
    if (!chosen)
        return;

    if (chosen == clearAll) {
        m_model->clear();
        return;
    }

    if (!hasRow)        // on a cliqué dans le vide : rien à copier
        return;

    const int row = idx.row();
    if (chosen == copyMsg) {
        copySelectedRow();
    }
    else if (chosen == copyRow) {
        QStringList cols;
        for (int c = 0; c < LogModel::Count; ++c)
            cols << m_model->data(m_model->index(row, c), Qt::DisplayRole).toString();
        QApplication::clipboard()->setText(cols.join("\t"));
    }
}
