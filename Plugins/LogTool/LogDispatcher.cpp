#include "LogDispatcher.h"

#include <QTextStream>      // sortie fichier
#include <QIODevice>        // flags d’ouverture

#include <QMutexLocker>
#include <QThread>          // currentThreadId()
#include <QMetaObject>      // invokeMethod
#include <QLoggingCategory> // éventuel nom de catégorie/type
#include <QMetaType>

#include <windows.h>

QFile* LogDispatcher::s_file = nullptr;
QMutex  LogDispatcher::s_fileMutex;

// ------------------------------------------------------------------
// Enregistrement du métatype LogEntry pour les connexions Queued
// ------------------------------------------------------------------
namespace {
const int _logEntryMetaId = []() {
    return qRegisterMetaType<LogEntry>("LogEntry");
}();
}

LogDispatcher& LogDispatcher::instance()
{
    static LogDispatcher d;
    return d;
}

LogDispatcher::LogDispatcher(QObject*)
{
    qInstallMessageHandler(&LogDispatcher::messageHandler);
}

void LogDispatcher::removeLogFile()
{
	QMutexLocker lock(&s_fileMutex);
	delete s_file;
	s_file = nullptr;
}

void LogDispatcher::setLogFile(const QString& path)
{
    QMutexLocker lock(&s_fileMutex);
    delete s_file;
    s_file = nullptr;
    if (!path.isEmpty()) {
        s_file = new QFile(path);
        if (!s_file->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
            s_file = nullptr;          // silencieux : on reste fonctionnel
    }
}

static inline QString tidHex()
{
    return QString::number(quintptr(QThread::currentThreadId()), 16).rightJustified(8, '0');
}

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

void LogDispatcher::messageHandler(QtMsgType t, const QMessageLogContext& c, const QString& m)
{
    LogEntry e{ QDateTime::currentDateTime(),
                t,
                QString::fromLatin1(c.category),
                QString::fromLatin1(c.file),
                c.line,
                tidHex(),
                m };

    // 1) diffusion dans le thread GUI
    QMetaObject::invokeMethod(&instance(), "newEntry", Qt::QueuedConnection, Q_ARG(LogEntry, e));

    // 2) sortie standard (console)
    if (t == QtDebugMsg || t == QtInfoMsg || t == QtWarningMsg || t == QtCriticalMsg) {
        QString out = QString("[%1] %2 (%3:%4) %5\n")
        .arg(levelStr(t))
            .arg(c.category)
            .arg(c.file)
            .arg(c.line)
            .arg(m);
        OutputDebugStringW(reinterpret_cast<const wchar_t*>(out.utf16()));
    }

    // 3) sortie fichier éventuelle
    QMutexLocker lock(&s_fileMutex);
    if (s_file) {
        QTextStream ts(s_file);
        ts << e.ts.toString(Qt::ISODateWithMs) << ' '
            << e.threadId << ' '
            << levelStr(e.type) << ' '
            << e.category << ' '
            << e.file << ':' << e.line << ' '
            << e.msg << '\n';
        ts.flush();
    }
}
