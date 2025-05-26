#include "ViewFactory.h"
#include "AppStore.h"
#include "AppConfig.h"

#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QStringList>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <memory>

bool setupApp(QString& errorMessage, QString& warningMessage);
AppConfig* createAppConfig(const QString& configFilePath);
void addToString(const QString& newMessage, QString& messageOut);
bool createFolder(const QString& folderName, const QString& folderPath, QString& errorMessage);
void checkFileExists(const QString& fileName, const QString& filePath, QString& warningMessage);

int main(int argc, char* argv[])
{
	//qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
	QApplication a(argc, argv);

	QString errorMessage;
	QString warningMessage;
	int status = -1;

	if (setupApp(errorMessage, warningMessage))
	{
		ViewFactory::createMainWindow()->showMaximized();

		if (!warningMessage.isEmpty())
		{
			for (const auto& m : warningMessage.split('\n'))
			{
				qWarning() << m;
			}
		}
		status = a.exec();
		AppConfig::deleteBackupConfig();
		AppStore::deleteAll();
	}
	else
	{
		QMessageBox::critical(nullptr, "Error", "Failed to setup application.\n" + errorMessage);
	}
	return status;
}

bool setupApp(QString& errorMessage, QString& warningMessage)
{
	QStringList args = QCoreApplication::arguments();
	AppConfig* appConfig = createAppConfig(args.size() > 1 ? args[1] : "");

	if (appConfig) {
		createFolder("Config folder", appConfig->getConfigFolder(), errorMessage);
		createFolder("Light control config folder", appConfig->getLightControlConfigFolder(), errorMessage);
		createFolder("Camera config folder", appConfig->getCameraConfigFolder(), errorMessage);
		createFolder("ROI config folder", appConfig->getRoiConfigFolder(), errorMessage);

		// Create config folders
		if (!errorMessage.isEmpty())
			return false;

		// Create config
		checkFileExists("Light control config", appConfig->getLightControlConfigPath(), warningMessage);
		checkFileExists("Camera config", appConfig->getCameraConfigPath(), warningMessage);
		checkFileExists("ROI config", appConfig->getRoiConfigPath(), warningMessage);
	}
	else
	{
		errorMessage = "Failed to create AppConfig.";
		return false;
	}

	return true;
}

AppConfig* createAppConfig(const QString& configFilePath)
{
	AppConfig* appConfig = nullptr;
	if (AppConfig::backupConfigFound() &&
		QMessageBox::question(nullptr, "Backup config",
			"A configuration backup file has been found. Would you like to recover this configuration? If you click \"No\", this backup will be lost.")
		== QMessageBox::StandardButton::Yes)
	{
		appConfig = AppConfig::openBackupConfig();
	}
	else
	{
		AppConfig::deleteBackupConfig();
		if (configFilePath.isEmpty())
		{
			QMessageBox::information(nullptr, "Config", "Config file not specified. A default config will be used.\n\nUsage: Vision.exe config-file");
			appConfig = new AppConfig();
		}
		else
		{
			bool configFullyLoaded;
			std::unique_ptr<AppConfig> pConfig = AppConfig::loadFromFile<AppConfig>(configFilePath, configFullyLoaded);
			if (pConfig)
				appConfig = pConfig.release();

			if (!appConfig && QMessageBox::question(nullptr, "Config", "Unable to load the config: " + configFilePath + ".\nDo you want to create a default config?")
				== QMessageBox::StandardButton::Yes)
			{
				appConfig = new AppConfig();
			}
		}
	}
	return appConfig;
}

void addToString(const QString& newMessage, QString& messageOut)
{
	messageOut += messageOut.isEmpty() ? newMessage : ('\n' + newMessage);
}

bool createFolder(const QString& folderName, const QString& folderPath, QString& errorMessage)
{
	if (folderPath.isEmpty())
	{
		addToString(folderName + ": path not specified.", errorMessage);
		return false;
	}

	QString absolutePath = QDir(folderPath).isRelative() ? QDir::current().absoluteFilePath(folderPath) : folderPath;
	QDir dir(absolutePath);

	if (!dir.exists())
	{
		if (!QDir().mkdir(absolutePath))
		{
			addToString(folderName + ": unable to create folder.", errorMessage);
			return false;
		}
	}
	else if (!dir.isReadable())
	{
		addToString(folderName + ": not readable.", errorMessage);
		return false;
	}
	return true;
}

void checkFileExists(const QString& fileName, const QString& filePath, QString& warningMessage)
{
	if (filePath.isEmpty())
	{
		addToString(fileName + ": file not specified.", warningMessage);
		return;
	}
	QFileInfo fileInfo(filePath);
	if (!fileInfo.exists())
	{
		addToString(fileName + ": file does not exist.", warningMessage);
	}
	else if (!fileInfo.isFile())
	{
		addToString(fileName + ": not a file.", warningMessage);
	}
	else if (!fileInfo.isReadable())
	{
		addToString(fileName + ": not readable.", warningMessage);
	}
}
