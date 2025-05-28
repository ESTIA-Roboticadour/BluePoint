#include "Helper.h"
#include "AppStore.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>

QString Helper::getSaveConfigFile(
    QWidget* parent,
    const QString& defaultFileName,
    const QString& defaultDir,
    const QString& filters)
{ 
    // Emplacement initial : Documents si non fourni
    const QString defaultConfigDir = AppStore::getAppConfig()->getConfigFolder();
    const QString initialDir = defaultDir.isEmpty() ?
        (defaultConfigDir.isEmpty() ? 
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) : defaultConfigDir) :
        defaultDir;

    // Chemin combiné "dossier/nom"
    const QString initialPath = defaultFileName.isEmpty() ?
        initialDir :
        QDir(initialDir).filePath(defaultFileName);

    QString selected =
        QFileDialog::getSaveFileName(parent,
            QObject::tr("Save configuration"),
            initialPath,
            filters);

    if (selected.isEmpty())
        return {};                              // Annulé

    // Ajoute ".json" si l'utilisateur a omis l'extension
    if (!selected.endsWith(".json", Qt::CaseInsensitive))
        selected += ".json";

    QString out = QDir::toNativeSeparators(selected);
    return out;
}
