#include "AppConfig.h"
#include "ListParameterBase.h"
#include <QFile>
#include <QVariant>
#include <QPair>
#include <memory>

AppConfig::AppConfig(QObject* parent) :
	Config(parent),
	m_folderGroup("Folders", this),
	m_pathGroup("Paths", this),
	m_deviceGroup("Devices", this),
	m_configFolder(CONFIG_FOLDER, CONFIG_FOLDER_DEFAULT_VALUE, StringParameter::Kind::DirectoryPath, this),
	m_appConfigFolder(APP_CONFIG_FOLDER, APP_CONFIG_FOLDER_DEFAULT_VALUE, StringParameter::Kind::DirectoryPath, this),
	m_lightControlConfigFolder(LIGHT_CONTROL_CONFIG_FOLDER, LIGHT_CONTROL_CONFIG_FOLDER_DEFAULT_VALUE, StringParameter::Kind::DirectoryPath, this),
	m_cameraConfigFolder(CAMERA_CONFIG_FOLDER, CAMERA_CONFIG_FOLDER_DEFAULT_VALUE, StringParameter::Kind::DirectoryPath, this),
	m_roiConfigFolder(ROI_CONFIG_FOLDER, ROI_CONFIG_FOLDER_DEFAULT_VALUE, StringParameter::Kind::DirectoryPath, this),
	m_cameraType("Camera Type", this),
	m_lightControlConfigPath(LIGHT_CONTROL_CONFIG_PATH, "", StringParameter::Kind::FilePath, this),
	m_cameraConfigPath(CAMERA_CONFIG_PATH, "", StringParameter::Kind::FilePath, this),
	m_roiConfigPath(ROI_CONFIG_PATH, "", StringParameter::Kind::FilePath, this)
{
	m_cameraType.addItem("Basler", "Basler");
	m_cameraType.addItem("RealSense", "RealSense");
	
	m_lightControlConfigPath.setCanEditPath(false);
	m_cameraConfigPath.setCanEditPath(false);
	m_roiConfigPath.setCanEditPath(false);

	addParameters();
}

AppConfig::AppConfig(const AppConfig& config, QObject* parent) :
	Config(config, parent),
	m_folderGroup("Folders", this),
	m_pathGroup("Paths", this),
	m_deviceGroup("Devices", this),
	m_configFolder(CONFIG_FOLDER, config.m_configFolder, this),
	m_appConfigFolder(APP_CONFIG_FOLDER, config.m_appConfigFolder, this),
	m_lightControlConfigFolder(LIGHT_CONTROL_CONFIG_FOLDER, config.m_lightControlConfigFolder, this),
	m_cameraConfigFolder(CAMERA_CONFIG_FOLDER, config.m_cameraConfigFolder, this),
	m_roiConfigFolder(ROI_CONFIG_FOLDER, config.m_roiConfigFolder, this),
	m_cameraType("Camera Type", this),
	m_lightControlConfigPath(LIGHT_CONTROL_CONFIG_PATH, config.m_lightControlConfigPath, this),
	m_cameraConfigPath(CAMERA_CONFIG_PATH, config.m_cameraConfigPath, this),
	m_roiConfigPath(ROI_CONFIG_PATH, config.m_roiConfigPath, this)
{
	m_configFolder.setKind(StringParameter::Kind::DirectoryPath);
	m_appConfigFolder.setKind(StringParameter::Kind::DirectoryPath);
	m_lightControlConfigFolder.setKind(StringParameter::Kind::DirectoryPath);
	m_cameraConfigFolder.setKind(StringParameter::Kind::DirectoryPath);
	m_roiConfigFolder.setKind(StringParameter::Kind::DirectoryPath);
	m_lightControlConfigPath.setKind(StringParameter::Kind::FilePath);
	m_cameraConfigPath.setKind(StringParameter::Kind::FilePath);
	m_roiConfigPath.setKind(StringParameter::Kind::FilePath);

	for (const auto& camera : config.m_cameraType.items())
	{
		m_cameraType.addItem(camera.first, camera.second.toString());
	}
	m_lightControlConfigPath.setCanEditPath(false);
	m_cameraConfigPath.setCanEditPath(false);
	m_roiConfigPath.setCanEditPath(false);
	addParameters();
}

QString AppConfig::getConfigFolder() const
{
	return m_configFolder.getValue();
}

QString AppConfig::getAppConfigFolder() const
{
	return m_appConfigFolder.getValue();
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

QString AppConfig::getCameraType() const
{
	return m_cameraType.getSelectedValue().toString();
}

void AppConfig::reset()
{
	AppConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* AppConfig::copy(QObject* parent)
{
	AppConfig* newConfig = new AppConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

//bool AppConfig::backupConfigFound()
//{
//	QFile file(BACKUP_FILE_PATH);
//	return file.exists();
//}

//void AppConfig::deleteBackupConfig()
//{
//	if (backupConfigFound())
//	{
//		QFile file(BACKUP_FILE_PATH);
//		if (file.remove())
//			qDebug() << "Backup config deleted.";
//		else
//			qWarning() << "Failed to delete backup config.";
//	}
//}

void AppConfig::addParameters()
{
	m_folderGroup.addParameter(&m_configFolder);
	m_folderGroup.addParameter(&m_appConfigFolder);
	m_folderGroup.addParameter(&m_lightControlConfigFolder);
	m_folderGroup.addParameter(&m_cameraConfigFolder);
	m_folderGroup.addParameter(&m_roiConfigFolder);

	m_deviceGroup.addParameter(&m_cameraType);

	m_pathGroup.addParameter(&m_lightControlConfigPath);
	m_pathGroup.addParameter(&m_cameraConfigPath);
	m_pathGroup.addParameter(&m_roiConfigPath);

	addParameter(&m_folderGroup);
	addParameter(&m_deviceGroup);
	addParameter(&m_pathGroup);
}

//AppConfig* AppConfig::openBackupConfig()
//{
//	if (backupConfigFound())
//	{
//		QFile file(BACKUP_FILE_PATH);
//		if (file.open(QIODevice::ReadOnly))
//		{
//			bool configFullyLoaded;
//			std::unique_ptr<AppConfig> pConfig = Config::loadFromFile<AppConfig>(BACKUP_FILE_PATH, configFullyLoaded);
//			if (pConfig)
//				return pConfig.release();
//			file.close();
//		}
//	}
//	return nullptr;
//}

bool AppConfig::setFromConfig(const Config* src, bool copyPath)
{
	int numberOfParametersToSet = 9;
	int numberOfParametersSet = 0;

	Config::setFromConfig(src, copyPath);
	if (src)
	{
		// Folders
		if (GroupParameter* group = qobject_cast<GroupParameter*>(src->getParameter("Folders")))
		{
			// Config
			if (StringParameter* folder = qobject_cast<StringParameter*>(group->getParameter(CONFIG_FOLDER)))
			{
				m_configFolder.setValue(folder->getValue());
				numberOfParametersSet++;
			}

			// App Config
			if (StringParameter* folder = qobject_cast<StringParameter*>(group->getParameter(APP_CONFIG_FOLDER)))
			{
				m_appConfigFolder.setValue(folder->getValue());
				numberOfParametersSet++;
			}

			// Light Control
			if (StringParameter* folder = qobject_cast<StringParameter*>(group->getParameter(LIGHT_CONTROL_CONFIG_FOLDER)))
			{
				m_lightControlConfigFolder.setValue(folder->getValue());
				numberOfParametersSet++;
			}

			// Camera
			if (StringParameter* folder = qobject_cast<StringParameter*>(group->getParameter(CAMERA_CONFIG_FOLDER)))
			{
				m_cameraConfigFolder.setValue(folder->getValue());
				numberOfParametersSet++;
			}

			// ROI
			if (StringParameter* folder = qobject_cast<StringParameter*>(group->getParameter(ROI_CONFIG_FOLDER)))
			{
				m_roiConfigFolder.setValue(folder->getValue());
				numberOfParametersSet++;
			}
		}

		// Devices
		if (GroupParameter* group = qobject_cast<GroupParameter*>(src->getParameter("Devices")))
		{
			// Camera type
			if (ListParameterBase* cameraList = qobject_cast<ListParameterBase*>(group->getParameter("Camera Type")))
			{
				m_cameraType.clear();
				for (const auto& item : cameraList->items())
				{
					m_cameraType.addItem(item.first, item.second.toString());
				}
				numberOfParametersSet++;
			}
		}

		// Paths
		if (GroupParameter* group = qobject_cast<GroupParameter*>(src->getParameter("Paths")))
		{
			// Light control config
			if (StringParameter* path = qobject_cast<StringParameter*>(group->getParameter(LIGHT_CONTROL_CONFIG_PATH)))
			{
				m_lightControlConfigPath.setValue(path->getValue());
				numberOfParametersSet++;
			}

			// Camera config
			if (StringParameter* path = qobject_cast<StringParameter*>(group->getParameter(CAMERA_CONFIG_PATH)))
			{
				m_cameraConfigPath.setValue(path->getValue());
				numberOfParametersSet++;
			}

			// ROI config
			if (StringParameter* path = qobject_cast<StringParameter*>(group->getParameter(ROI_CONFIG_PATH)))
			{
				m_roiConfigPath.setValue(path->getValue());
				numberOfParametersSet++;
			}
		}
	}
	return numberOfParametersSet == numberOfParametersToSet;
}
