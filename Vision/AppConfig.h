#pragma once
#include "Config.h"
#include "StringParameter.h"
#include "ListParameterBase.h"
#include "ListParameter.h"
#include "GroupParameter.h"

#include <QObject>
#include <QString>

class AppConfig : public Config
{
	Q_OBJECT

public:
	explicit AppConfig(QObject* parent = nullptr);
	AppConfig(const AppConfig& config, QObject* parent = nullptr);
	~AppConfig() override = default;

	// folder

	QString getConfigFolder() const;
	QString getAppConfigFolder() const;
	QString getLightControlConfigFolder() const;
	QString getCameraConfigFolder() const;
	QString getRoiConfigFolder() const;
	
	// path

	QString getLightControlConfigPath() const;
	QString getCameraConfigPath() const;
	QString getRoiConfigPath() const;

	// folder

	void setConfigFolder(const QString& path);
	void setLightControlConfigFolder(const QString& folder);
	void setCameraConfigFolder(const QString& folder);
	void setRoiConfigFolder(const QString& folder);
	
	// path

	void setLightControlConfigPath(const QString& path);
	void setCameraConfigPath(const QString& path);
	void setRoiConfigPath(const QString& path);

	QString getCameraType() const;

	void reset() override;
	Config* copy(QObject* parent=nullptr) override;

	bool areCameraTypeAndCameraConfigValid() const;
	bool isRoiConfigValid() const;
	bool isLightControlConfigValid() const;

	// static

	//static bool backupConfigFound();
	//static void deleteBackupConfig();
	//static AppConfig* openBackupConfig();

private:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void addParameters();

private:
	GroupParameter m_folderGroup;
	GroupParameter m_deviceGroup;
	GroupParameter m_pathGroup;

	// folder

	StringParameter m_configFolder;
	StringParameter m_appConfigFolder;
	StringParameter m_lightControlConfigFolder;
	StringParameter m_cameraConfigFolder;
	StringParameter m_roiConfigFolder;

	ListParameter<QString> m_cameraType;

	// path
	StringParameter m_lightControlConfigPath;
	StringParameter m_cameraConfigPath;
	StringParameter m_roiConfigPath;

	static const inline QString CONFIG_FOLDER = "Config Folder";
	static const inline QString APP_CONFIG_FOLDER = "App Config Folder";
	static const inline QString LIGHT_CONTROL_CONFIG_FOLDER = "Light Control Config Folder";
	static const inline QString CAMERA_CONFIG_FOLDER = "Camera Config Folder";
	static const inline QString ROI_CONFIG_FOLDER = "ROI Config Folder";

	static const inline QString LIGHT_CONTROL_CONFIG_PATH = "Light Control Config Path";
	static const inline QString CAMERA_CONFIG_PATH = "Camera Config Path";
	static const inline QString ROI_CONFIG_PATH = "ROI Config Path";

	static const inline QString CONFIG_FOLDER_DEFAULT_VALUE = "Config";
	static const inline QString APP_CONFIG_FOLDER_DEFAULT_VALUE = "Config/App";
	static const inline QString LIGHT_CONTROL_CONFIG_FOLDER_DEFAULT_VALUE = "Config/Light Control";
	static const inline QString CAMERA_CONFIG_FOLDER_DEFAULT_VALUE = "Config/Camera";
	static const inline QString ROI_CONFIG_FOLDER_DEFAULT_VALUE = "Config/ROI";
	
	static const inline QString BACKUP_FILE_PATH = APP_CONFIG_FOLDER_DEFAULT_VALUE + "/backup.json";
};
