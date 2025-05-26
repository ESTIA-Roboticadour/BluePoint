#include "AppSetup.h"
#include "AppConfig.h"
#include "AppStore.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

#include <memory>

// ---------------------------------------------------------------------
// Tout ce qui suit est *privé* au fichier (namespace anonyme)
// ---------------------------------------------------------------------
namespace {

    enum class MsgSeverity { Info, Warning, Error };

    struct MsgEntry
    {
        MsgSeverity severity;
        QString     text;
    };

    QVector<MsgEntry> g_messages;
    QString           g_errorMessage;

    std::unique_ptr<AppConfig> g_appConfig;   // RAII, évite fuite mémoire

    // ---------------------------------------------------------------------
    // Outils internes
    // ---------------------------------------------------------------------

    void addMsg(MsgSeverity s, const QString& txt)
    {
        g_messages.push_back({ s, txt });
    }

    inline void addInfo(const QString& txt) { addMsg(MsgSeverity::Info, txt); }
    inline void addWarning(const QString& txt) { addMsg(MsgSeverity::Warning, txt); }
    inline void addError(const QString& txt) { addMsg(MsgSeverity::Error, txt); g_errorMessage += g_errorMessage.isEmpty() ? txt : ('\n' + txt); }

    bool createFolder(const QString& logicalName, const QString& folderPath)
    {
        if (folderPath.isEmpty())
        {
			addError(logicalName + ": path not specified.");
            return false;
        }

        QString absolutePath =
            QDir(folderPath).isRelative()
            ? QDir::current().absoluteFilePath(folderPath)
            : folderPath;

        QDir dir(absolutePath);
        if (!dir.exists())
        {
            if (!QDir().mkdir(absolutePath))
            {
                addError(logicalName + ": unable to create folder.");
                return false;
            }
        }
        else if (!dir.isReadable())
        {
            addError(logicalName + ": not readable.");
            return false;
        }
        return true;
    }

    void checkFileExists(const QString& logicalName, const QString& filePath)
    {
        if (filePath.isEmpty())
        {
            addWarning(logicalName + ": file not specified.");
            return;
        }

        QFileInfo fi(filePath);
        if (!fi.exists())
            addWarning(logicalName + ": file does not exist.");
        else if (!fi.isFile())
            addWarning(logicalName + ": not a file.");
        else if (!fi.isReadable())
            addWarning(logicalName + ": not readable.");
    }

    AppConfig* createAppConfig(const QString& pathFromCli)
    {
        AppConfig* result = nullptr;

        if (AppConfig::backupConfigFound() &&
            QMessageBox::question(nullptr,
                "Backup config",
                "A configuration backup file has been found. "
                "Would you like to recover this configuration? "
                "If you click \"No\", this backup will be lost.")
            == QMessageBox::Yes)
        {
            result = AppConfig::openBackupConfig();
        }
        else
        {
            AppConfig::deleteBackupConfig();

            if (pathFromCli.isEmpty())
            {
                addInfo("Config file not specified. A default config will be used. Best usage: Vision.exe config-file");
                result = new AppConfig{};
            }
            else
            {
                bool fullyLoaded = false;
                std::unique_ptr<AppConfig> tmp =
                    AppConfig::loadFromFile<AppConfig>(pathFromCli, fullyLoaded);

                if (tmp)
                    result = tmp.release();

                if (!result &&
                    QMessageBox::question(nullptr,
                        "Config",
                        "Unable to load the config: " + pathFromCli +
                        ".\nDo you want to create a default "
                        "config?")
                    == QMessageBox::Yes)
                {
                    result = new AppConfig{};
                }
            }
        }
        return result;
    }

} // namespace (anonyme)

// ---------------------------------------------------------------------
// API publique d'AppSetup
// ---------------------------------------------------------------------
bool AppSetup::setupApp()
{
    const QStringList args = QCoreApplication::arguments();

    g_appConfig.reset(createAppConfig(args.size() > 1 ? args[1] : QString{}));
    if (!g_appConfig)
    {
        g_errorMessage = "Failed to create AppConfig.";
        return false;
    }

    // --- Création des dossiers indispensables ---
    createFolder("Config folder", g_appConfig->getConfigFolder());
    createFolder("Light control config", g_appConfig->getLightControlConfigFolder());
    createFolder("Camera config folder", g_appConfig->getCameraConfigFolder());
    createFolder("ROI config folder", g_appConfig->getRoiConfigFolder());

    if (!g_errorMessage.isEmpty())
        return false;

    // --- Vérification existence fichiers de config ---
    checkFileExists("Light control config", g_appConfig->getLightControlConfigPath());
    checkFileExists("Camera config", g_appConfig->getCameraConfigPath());
    checkFileExists("ROI config", g_appConfig->getRoiConfigPath());

    return true;
}

void AppSetup::shareMessages()
{
    for (const auto& m : g_messages)
    {
        switch (m.severity)
        {
        case MsgSeverity::Info:
            qInfo().noquote() << m.text;
            break;
        case MsgSeverity::Warning:
            qWarning().noquote() << m.text;
            break;
        case MsgSeverity::Error:
            qCritical().noquote() << m.text;
            break;
        }
    }
}


void AppSetup::showError(QWidget* parent)
{
    if (!g_errorMessage.isEmpty())
    {
        QMessageBox::critical(parent,
            "Error",
            "Failed to setup application.\n" + g_errorMessage);
    }
}
