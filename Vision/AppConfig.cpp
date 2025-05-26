#include "AppConfig.h"
#include <QFile>
#include <memory>

const QString AppConfig::BACKUP_FILE_PATH = "Config/Backup.json";

AppConfig::AppConfig(QObject* parent) :
	Config(parent),
	m_folderGroup("Folders", this),
	m_pathGroup("Config", this),
	m_configFolder("Config Folder", "Config", this),
	m_lightControlConfigFolder("Light Control Folder", "Config/Light Control", this),
	m_cameraConfigFolder("Camera Config Folder", "Config/Camera", this),
	m_roiConfigFolder("ROI Config Folder", "Config/ROI", this),
	m_lightControlConfigPath("Light Control Config Path", "", this),
	m_cameraConfigPath("Light Control Config Path", "", this),
	m_roiConfigPath("Light Control Config Path", "", this)
{
	addParameters();
}

AppConfig::AppConfig(const AppConfig& config, QObject* parent) :
	Config(parent),
	m_folderGroup("Folders", this),
	m_pathGroup("Config", this),
	m_configFolder("Config Folder", config.m_configFolder, this),
	m_lightControlConfigFolder("Light Control Folder", config.m_lightControlConfigFolder, this),
	m_cameraConfigFolder("Camera Config Folder", config.m_cameraConfigFolder, this),
	m_roiConfigFolder("ROI Config Folder", config.m_roiConfigFolder, this),
	m_lightControlConfigPath("Light Control Config Path", config.m_lightControlConfigPath, this),
	m_cameraConfigPath("Light Control Config Path", config.m_cameraConfigPath, this),
	m_roiConfigPath("Light Control Config Path", config.m_roiConfigPath, this)
{
	addParameters();
}

QString AppConfig::getConfigFolder() const
{
	return m_configFolder.getValue();
}

QString AppConfig::getLightControlConfigFolder() const
{
	return m_lightControlConfigFolder.getValue();
}

QString AppConfig::getCameraConfigFolder() const
{
	return m_cameraConfigFolder.getValue();
}

QString AppConfig::getRoiConfigFolder() const
{
	return m_roiConfigFolder.getValue();
}

QString AppConfig::getLightControlConfigPath() const
{
	return m_lightControlConfigPath.getValue();
}

QString AppConfig::getCameraConfigPath() const
{
	return m_cameraConfigPath.getValue();
}

QString AppConfig::getRoiConfigPath() const
{
	return m_roiConfigPath.getValue();
}

void AppConfig::setConfigFolder(const QString& folder)
{
	m_configFolder.setValue(folder);
}
void AppConfig::setLightControlConfigFolder(const QString& folder)
{
	m_lightControlConfigFolder.setValue(folder);
}

void AppConfig::setCameraConfigFolder(const QString& folder)
{
	m_cameraConfigFolder.setValue(folder);
}

void AppConfig::setRoiConfigFolder(const QString& folder)
{
	m_roiConfigFolder.setValue(folder);
}

void AppConfig::setLightControlConfigPath(const QString& path)
{
	m_lightControlConfigPath.setValue(path);
}

void AppConfig::setCameraConfigPath(const QString& path)
{
	m_cameraConfigPath.setValue(path);
}

void AppConfig::setRoiConfigPath(const QString& path)
{
	m_roiConfigPath.setValue(path);
}

bool AppConfig::backupConfigFound()
{
	QFile file(BACKUP_FILE_PATH);
	return file.exists();
}

void AppConfig::deleteBackupConfig()
{
	if (backupConfigFound())
	{
		QFile file(BACKUP_FILE_PATH);
		if (file.remove())
			qDebug() << "Backup config deleted.";
		else
			qWarning() << "Failed to delete backup config.";
	}
}

void AppConfig::addParameters()
{
	m_folderGroup.addParameter(&m_configFolder);
	m_folderGroup.addParameter(&m_lightControlConfigFolder);
	m_folderGroup.addParameter(&m_cameraConfigFolder);
	
	m_pathGroup.addParameter(&m_roiConfigFolder);
	m_pathGroup.addParameter(&m_lightControlConfigPath);
	m_pathGroup.addParameter(&m_cameraConfigPath);
	m_pathGroup.addParameter(&m_roiConfigPath);

	addParameter(&m_folderGroup);
	addParameter(&m_pathGroup);
}

AppConfig* AppConfig::openBackupConfig()
{
	if (backupConfigFound())
	{
		QFile file(BACKUP_FILE_PATH);
		if (file.open(QIODevice::ReadOnly))
		{
			bool configFullyLoaded;
			std::unique_ptr<AppConfig> pConfig = Config::loadFromFile<AppConfig>(BACKUP_FILE_PATH, configFullyLoaded);
			if (pConfig)
				return pConfig.release();
			file.close();
		}
	}
	return nullptr;
}

bool AppConfig::setFromConfig(const Config* src)
{
	return true;
}
