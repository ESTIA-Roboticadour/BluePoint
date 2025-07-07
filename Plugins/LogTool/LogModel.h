#ifndef LOGMODEL_H
#define LOGMODEL_H

#include "LogTool_global.h"

#include <QObject>
#include <QAbstractTableModel>
#include <QVector>
#include <QDateTime>
#include <QColor>
#include <array>

#include "LogDispatcher.h"   // LogEntry

static constexpr int kMsgTypeCount = (QtInfoMsg > QtFatalMsg ? QtInfoMsg : QtFatalMsg) + 1;

class LOGTOOL_API LogModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Column { Time, Level, /*Thread, Category, File,*/ Message, Count };

    explicit LogModel(QObject* parent = nullptr);

    // QAbstractItemModel
    int      rowCount(const QModelIndex& parent = {}) const override;
    int      columnCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /* --- Couleurs configurables ------------------------------------ */
    void   setColor(QtMsgType type, const QColor& c);   // ex. QtWarningMsg
    QColor getColor(QtMsgType type) const;

public slots:
    void append(const LogEntry& entry);
    void clear();

private:
    QVector<LogEntry>                 m_entries;
    std::array<QColor, kMsgTypeCount> m_colors;  // indexé par QtMsgType
};

#endif // LOGMODEL_H
