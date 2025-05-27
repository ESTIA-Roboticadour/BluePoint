#pragma once
#include "Config.h"
#include "StringParameter.h"
#include "GroupParameter.h"

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

	static bool backupConfigFound();
	static void deleteBackupConfig();
	static AppConfig* openBackupConfig();

protected:
	bool setFromConfig(const Config* src) override;

private:
	void addParameters();

private:
	GroupParameter m_folderGroup;
	GroupParameter m_pathGroup;

	// folder

	StringParameter m_configFolder;
	StringParameter m_appConfigFolder;
	StringParameter m_lightControlConfigFolder;
	StringParameter m_cameraConfigFolder;
	StringParameter m_roiConfigFolder;

	// path
	StringParameter m_lightControlConfigPath;
	StringParameter m_cameraConfigPath;
	StringParameter m_roiConfigPath;

	static const QString BACKUP_FILE_PATH;
};
