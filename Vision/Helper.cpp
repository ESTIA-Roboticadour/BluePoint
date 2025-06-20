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

QString Helper::getOpenConfigFile(
    QWidget* parent,
    const QString& defaultDir,
    const QString& filters)
{
    // Emplacement initial : dossier de configuration de l'application,
    // puis Documents si rien n’est configuré.
    const QString defaultConfigDir = AppStore::getAppConfig()->getConfigFolder();
    const QString initialDir = defaultDir.isEmpty()
        ? (defaultConfigDir.isEmpty()
            ? QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
            : defaultConfigDir)
        : defaultDir;

    QString selected = QFileDialog::getOpenFileName(parent,
        QObject::tr("Open configuration"),
        initialDir,
        filters);
    if (selected.isEmpty())
        return {};                         // utilisateur : Annuler

    // Normalise le chemin et, par sécurité, force l’extension « .json »
    if (!selected.endsWith(".json", Qt::CaseInsensitive))
        selected += ".json";

    return QDir::toNativeSeparators(selected);
}

QString Helper::makePathAbsolute(const QString& path)
{
    if (path.isEmpty())
        return {};

    QFileInfo fi(path);

    if (fi.isAbsolute())
        return QDir::cleanPath(fi.absoluteFilePath());

    // Construit un nouveau QFileInfo relatif au répertoire courant
    fi.setFile(QDir::current(), path);
    return QDir::cleanPath(fi.absoluteFilePath());
}
