#include "LogDispatcher.h"
#include "AppSetup.h"
#include "AppStore.h"
#include "LightControlConfig.h"
#include "RoiConfig.h"
#include "BaslerCameraConfig.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

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

QCommandLineParser* AppSetup::buildParser()
{
	QCommandLineParser* parser = new QCommandLineParser();
	parser->setApplicationDescription("BluePoint");
	parser->addHelpOption();
	parser->addPositionalArgument("config", QCoreApplication::translate("main", "Chemin vers le fichier .json de configuration."));
	parser->process(QCoreApplication::arguments());
	return parser;
}

void AppSetup::setupSettings()
{
	// On cherche d’abord près de l'exécutable
	QString iniPath = QCoreApplication::applicationDirPath() + "/config.ini";

	// Ou, à défaut, dans le dossier de conf système
	//if (!QFileInfo::exists(iniPath)) {
	//	iniPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/config.ini";
	//}

	QSettings* ini = new QSettings(iniPath, QSettings::IniFormat);
	ini->beginGroup("General");
	if (!ini->contains("AppConfigPath"))
	{
		ini->setValue("AppConfigPath", "Config/App/default.json");
	}
	ini->endGroup();
	ini->sync();
	AppStore::setSettings(ini);
}

QString AppSetup::getConfigPath(const QCommandLineParser* parser)
{
	return !parser->positionalArguments().isEmpty() ?
		parser->positionalArguments().first() :
		AppStore::getAppConfigPath();
}

bool AppSetup::createFolder(const QString& logicalName, const QString& folderPath)
{
	if (folderPath.isEmpty())
	{
		addError(logicalName + ": path not specified.");
		return false;
	}

	QString absolutePath = QDir(folderPath).isRelative() ?
		QDir::current().absoluteFilePath(folderPath) :
		folderPath;

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
	QString path = QDir::currentPath() + '/' + AppStore::getDefaultAppConfigPath();

	if (result && result->save(path))
	{
		addInfo("Default config saved at: " + AppStore::getDefaultAppConfigPath());
	}
	else
	{
		addError("Failed to save default config at: " + AppStore::getDefaultAppConfigPath());
		if (result)
			delete result;
		result = nullptr;
	}
	return result;
}

AppConfig* AppSetup::createAppConfig(const QString& filepath)
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
		if (result)
			return result;
		else
		{
			QMessageBox::warning(nullptr, "Backup config", "Backup file not loaded.");
			addWarning("Backup file not loaded.");
		}
	}
	AppConfig::deleteBackupConfig();

	if (filepath.isEmpty())
	{
		addInfo("Config file not specified. To specify a config file, use: Vision.exe [config-file]    or edit config.ini file.");
		result = loadAppConfigFromNothing();
	}
	if (QFile::exists(filepath))
	{
		result = loadAppConfigFromFile(filepath);
		if (!result)
		{
			addWarning(filepath + " not loaded.");
			result = loadAppConfigFromNothing();
		}
	}
	else
	{
		addWarning(filepath + " not found.");
		result = loadAppConfigFromNothing();
	}
	return result;
}

AppConfig* AppSetup::loadAppConfigFromNothing()
{
	AppConfig* result = nullptr;
	QString path = QDir::currentPath() + '/' + AppStore::getDefaultAppConfigPath();
	if (QFile::exists(path))
	{
		if (QMessageBox::question(nullptr, "Config file", "Config file is not specified, or not found or couldn't be loaded.\n" +
			path + " found.\nDo you want to use it?")
			== QMessageBox::Yes)
		{
			result = loadAppConfigFromDefault();
		}
	}
	else
	{
		if (QMessageBox::question(nullptr, "Config file", 
			"Config file is not specified, or not found or couldn't be loaded.\nDefault config file not found.\nDo you want to create a new config?")
			== QMessageBox::Yes)
		{
			result = createDefaultAppConfig();
		}
	}
	return result;
}

AppConfig* AppSetup::loadAppConfigFromDefault()
{
	AppConfig* result = loadAppConfigFromFile(AppStore::getDefaultAppConfigPath());

	if (!result &&
		QMessageBox::question(nullptr,
			"Config",
			"Unable to load the config: " + AppStore::getDefaultAppConfigPath() +
			".\nDo you want to create a default "
			"config?")
		== QMessageBox::Yes)
	{
		result = createDefaultAppConfig();
	}
	return result;
}

AppConfig* AppSetup::loadAppConfigFromFile(const QString& filepath)
{
	AppConfig* result = nullptr;
	addInfo("Opening: " + filepath);

	bool fullyLoaded = false;
	std::unique_ptr<AppConfig> tmp = AppConfig::loadFromFile<AppConfig>(filepath, fullyLoaded);

	if (tmp)
		result = tmp.release();

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

CameraConfig* AppSetup::tryLoadCameraConfig(const QString& camera, const QString& filePath)
{
	CameraConfig* config = nullptr;
	if (camera == "Basler")
	{
		BaslerCameraConfig* baslerConfig = tryLoadConfig<BaslerCameraConfig>("Basler camera config", filePath);
		if (baslerConfig)
			config = baslerConfig;
	}
	else
	{
		addError("Unknown camera type: " + camera + ". No camera set.");
	}
	return config;
}

// ---------------------------------------------------------------------
// API publique d'AppSetup
// ---------------------------------------------------------------------
bool AppSetup::setupApp()
{
	QCommandLineParser* parser = buildParser();
	setupSettings();
	LogDispatcher::setLogFile("Vision.log");

	g_appConfig.reset(createAppConfig(getConfigPath(parser)));
	delete parser;

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
	LightControlConfig* lightControlConfig = tryLoadConfig<LightControlConfig>("Light control config", g_appConfig->getLightControlConfigPath());
	CameraConfig* cameraConfig = tryLoadCameraConfig(g_appConfig->getCameraType(), g_appConfig->getCameraConfigPath());
	RoiConfig* roiConfig = tryLoadConfig<RoiConfig>("ROI config", g_appConfig->getRoiConfigPath());

	AppStore::init(
		g_appConfig.release(),
		lightControlConfig,
		cameraConfig,
		roiConfig
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
