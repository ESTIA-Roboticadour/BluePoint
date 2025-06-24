#ifndef LOGDISPATCHER_H
#define LOGDISPATCHER_H

#include "LogTool_global.h"

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QtGlobal>     // QtMsgType, quintptr, qInstallMessageHandler
#include <QMutex>       // QMutex, QMutexLocker
#include <QFile>        // QFile* + ouvertures
#include <QMetaType>

struct LogEntry
{
    QDateTime ts;          // horodatage
    QtMsgType type;
    QString   category;
    QString   file;
    int       line;
    QString   threadId;    // hex string
    QString   msg;
};

Q_DECLARE_METATYPE(LogEntry)

class LOGTOOL_API LogDispatcher : public QObject
{
    Q_OBJECT
public:
    static LogDispatcher& instance();

    /**  Active / change le fichier cible (vide => plus de fichier). */
    static void setLogFile(const QString& absolutePath);
    static void removeLogFile();
    static void setUILogEnabled(bool uiLogEnabled);
    static void showConsoleOutput(bool enable);

signals:
    void newEntry(const LogEntry& e);

private:
    explicit LogDispatcher(QObject* parent = nullptr);
    static void messageHandler(QtMsgType t, const QMessageLogContext& c, const QString& m);

    static QFile* s_file;         // nullptr si aucun
    static QMutex s_fileMutex;    // protège s_file

    static bool s_uiLogEnabled;
    static bool s_showConsoleOutput;
};

#endif // LOGDISPATCHER_H
