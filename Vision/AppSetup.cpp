#include "LogDispatcher.h"
#include "AppSetup.h"
#include "AppStore.h"
#include "LightControlConfig.h"
#include "CameraConfig.h"
#include "RoiConfig.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

QVector<AppSetup::MsgEntry> AppSetup::g_messages;
QString                     AppSetup::g_errorMessage;

std::unique_ptr<AppConfig> AppSetup::g_appConfig;

void AppSetup::addMsg(MsgSeverity s, const QString& txt)
{
	g_messages.push_back({ s, txt });
}

void AppSetup::addInfo(const QString& txt) { addMsg(MsgSeverity::Info, txt); }
void AppSetup::addWarning(const QString& txt) { addMsg(MsgSeverity::Warning, txt); }
void AppSetup::addError(const QString& txt, bool critical)
{
	addMsg(MsgSeverity::Error, txt);
	if (critical)
		g_errorMessage += g_errorMessage.isEmpty() ? txt : ('\n' + txt);
}

bool AppSetup::createFolder(const QString& logicalName, const QString& folderPath)
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

AppConfig* AppSetup::createDefaultAppConfig()
{
	AppConfig* result = new AppConfig();
	if (result && result->save(DEFAULT_FILE_PATH))
	{
		addInfo("Default config saved at: " + DEFAULT_FILE_PATH);
	}
	else
	{
		addError("Failed to save default config at: " + DEFAULT_FILE_PATH);
		if (result)
			delete result;
		result = nullptr;
	}
	return result;
}

AppConfig* AppSetup::createAppConfig(const QString& pathFromCli)
{
	QString filePath = pathFromCli.isEmpty() ? DEFAULT_FILE_PATH : pathFromCli;

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
			addInfo("Config file not specified.");
			if (QFile::exists(DEFAULT_FILE_PATH))
			{
				addInfo("Using default config file: " + DEFAULT_FILE_PATH);
				addInfo("To specify a config file: Vision.exe [config-file]");

				// config is opened in next block with filePath
			}
			else
			{
				addInfo("No default config file found. Creating a new one.");
				result = createDefaultAppConfig();
			}
		}

		if (!result && !filePath.isEmpty())
		{
			bool fullyLoaded = false;
			std::unique_ptr<AppConfig> tmp = AppConfig::loadFromFile<AppConfig>(filePath, fullyLoaded);

			if (tmp)
				result = tmp.release();

			if (!result &&
				QMessageBox::question(nullptr,
					"Config",
					"Unable to load the config: " + filePath +
					".\nDo you want to create a default "
					"config?")
				== QMessageBox::Yes)
			{
				result = createDefaultAppConfig();
			}
		}
	}
	return result;
}


bool AppSetup::checkFileExists(const QString& logicalName, const QString& filePath)
{
	bool exists = false;
	if (filePath.isEmpty())
	{
		addWarning(logicalName + ": file not specified.");
	}
	else
	{
		QFileInfo fi(filePath);
		if (!fi.exists())
			addWarning(logicalName + ": file does not exist.");
		else if (!fi.isFile())
			addWarning(logicalName + ": not a file.");
		else if (!fi.isReadable())
			addWarning(logicalName + ": not readable.");
		else
			exists = true;
	}
	return exists;

}

// ---------------------------------------------------------------------
// API publique d'AppSetup
// ---------------------------------------------------------------------
bool AppSetup::setupApp()
{
	LogDispatcher::setLogFile("Vision.log");

	const QStringList args = QCoreApplication::arguments();

	g_appConfig.reset(createAppConfig(args.size() > 1 ? args[1] : QString()));
	if (!g_appConfig)
	{
		g_errorMessage = "Failed to create AppConfig.";
		return false;
	}

	// --- Création des dossiers indispensables ---
	createFolder("Config folder", g_appConfig->getConfigFolder());
	createFolder("App config folder", g_appConfig->getAppConfigFolder());
	createFolder("Light control config folder", g_appConfig->getLightControlConfigFolder());
	createFolder("Camera config folder", g_appConfig->getCameraConfigFolder());
	createFolder("ROI config folder", g_appConfig->getRoiConfigFolder());

	if (!g_errorMessage.isEmpty())
		return false;

	// --- Vérification existence fichiers de config et création des configs ---
	LightControlConfig*  lightControlConfig = tryLoadConfig<LightControlConfig>("Light control config", g_appConfig->getLightControlConfigPath());
	CameraConfig* cameraConfig = tryLoadConfig<CameraConfig>("Camera config", g_appConfig->getCameraConfigPath());
	RoiConfig* roiConfig = tryLoadConfig<RoiConfig>("ROI config", g_appConfig->getRoiConfigPath());

	AppStore::init(
		g_appConfig.release(),
		lightControlConfig,
		cameraConfig,
		roiConfig,
		nullptr//Camera::getInstance()
	);
	
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
