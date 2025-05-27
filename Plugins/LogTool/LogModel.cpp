#include "LogModel.h"

#include <QFileInfo>
#include <QApplication>
#include <QPalette>
#include <QString>

static constexpr const char* kHeaderTitles[] = {
    "Time", "Lvl", "Thread", "Cat.", "File:Line", "Message"
};

static constexpr const char* levelStr(QtMsgType t)
{
    switch (t) {
    case QtDebugMsg:    return "DBG";
    case QtInfoMsg:     return "INF";
    case QtWarningMsg:  return "WRN";
    case QtCriticalMsg: return "CRT";
    case QtFatalMsg:    return "FTL";
    }
    return "UNK";
}

static inline QString dequote(QString s)
{
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        s = s.mid(1, s.size() - 2);
    return s;
}

/* ------------------------------------------------------------------ */
/* ctor : couleurs par défaut                                         */
/* ------------------------------------------------------------------ */
LogModel::LogModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    const QPalette pal = qApp->palette();
    m_colors[QtDebugMsg]    = QColor(150, 150, 150);           // gray
    m_colors[QtInfoMsg]     = pal.color(QPalette::WindowText); // theme color
    m_colors[QtWarningMsg]  = QColor(255, 210, 0);             // yellow
    m_colors[QtCriticalMsg] = QColor(Qt::red);                 // red
    m_colors[QtFatalMsg]    = QColor(139, 0, 0);               // dark red
}

/* ------------------------------------------------------------------ */
/* QAbstractTableModel                                                */
/* ------------------------------------------------------------------ */
int LogModel::rowCount(const QModelIndex&) const { return m_entries.size(); }
int LogModel::columnCount(const QModelIndex&) const { return Count; }

QVariant LogModel::data(const QModelIndex& idx, int role) const
{
    if (!idx.isValid() || idx.row() >= m_entries.size())
        return {};

    const LogEntry& e = m_entries.at(idx.row());

    if (role == Qt::DisplayRole) {
        switch (idx.column()) {
        case Time:     return e.ts.toString("HH:mm:ss.zzz");
        case Level:    return levelStr(e.type);
        case Thread:   return e.threadId;
        case Category: return e.category;
        case File:     return QFileInfo(e.file).fileName()
            + ':' + QString::number(e.line);
        case Message:  return dequote(e.msg);
        }
    }
    else if (role == Qt::ForegroundRole) {
        return m_colors[e.type];
    }
    return {};
}

QVariant LogModel::headerData(int section, Qt::Orientation o, int role) const
{
    if (o == Qt::Horizontal && role == Qt::DisplayRole && section < Count)
        return kHeaderTitles[section];
    return {};
}

/* ------------------------------------------------------------------ */
/* Append                                                             */
/* ------------------------------------------------------------------ */
void LogModel::append(const LogEntry& entry)
{
    beginInsertRows({}, m_entries.size(), m_entries.size());
    m_entries.push_back(entry);
    endInsertRows();
}

void LogModel::clear()
{
    beginResetModel();
    m_entries.clear();
    endResetModel();
}

/* ------------------------------------------------------------------ */
/* Couleurs utilisateur                                               */
/* ------------------------------------------------------------------ */
void LogModel::setColor(QtMsgType type, const QColor& c)
{
    if (type >= 0 && type < m_colors.size())
        m_colors[type] = c;
}

QColor LogModel::getColor(QtMsgType type) const
{
    return (type >= 0 && type < m_colors.size()) ? m_colors[type] : QColor();
}
