#pragma once

#include "AppConfig.h"
#include "CameraConfig.h"

#include <QString>
#include <QWidget>
#include <QCommandLineParser>
#include <memory>
#include <type_traits>

class AppSetup
{
private:

	enum class MsgSeverity { Info, Warning, Error };
	struct MsgEntry
	{
		MsgSeverity severity;
		QString     text;
	};

public:
	// Interdire construction / copie
	AppSetup() = delete;
	AppSetup(const AppSetup&) = delete;
	AppSetup& operator=(const AppSetup&) = delete;

	/// Prépare l’application.  Renvoie true si tout est OK.
	static bool setupApp();

	/// Affiche toutes les infos et warnings emmagasinées pendant setup.
	static void shareMessages();

	/// Affiche la boîte de dialogue d’erreur (s’il y a eu échec).
	static void showError(QWidget* parent = nullptr);

private:

	static void addMsg(MsgSeverity s, const QString& txt);

	static inline void addInfo(const QString& txt);
	static inline void addWarning(const QString& txt);
	static inline void addError(const QString& txt, bool critical = true);

	static QCommandLineParser* buildParser();
	static void setupSettings();

	static inline QString getConfigPath(const QCommandLineParser* parser);

	static bool createFolder(const QString& logicalName, const QString& folderPath);
	static AppConfig* createDefaultAppConfig();

	static AppConfig* createAppConfig(const QString& filepath);
	static AppConfig* loadAppConfigFromNothing();
	static AppConfig* loadAppConfigFromDefault();
	static AppConfig* loadAppConfigFromFile(const QString& filepath);

	static bool checkFileExists(const QString& logicalName, const QString& filePath);

	template<typename T = Config, std::enable_if_t<std::is_base_of_v<Config, T>, int> = 0>
	static T* tryLoadConfig(const QString& configName, const QString& path)
	{
		T* out = nullptr;

		if (checkFileExists(configName, path))
		{
			bool fullyLoaded;
			std::unique_ptr<T> tmp = Config::loadFromFile<T>(path, fullyLoaded);
			if (tmp)
			{
				if (fullyLoaded)
				{
					addInfo(configName + " loaded from: " + path);
				}
				else
				{
					addWarning(configName + " partially loaded from: " + path + "\nYou must check the configuration");
				}
				out = tmp.release();
			}
			else
			{
				addError("Failed to load: " + configName + " from: " + path, false);
				addWarning("You must configure it");
			}
		}
		else
		{
			addWarning("You must configure it");
		}
		return out;
	}

	static CameraConfig* tryLoadCameraConfig(const QString& camera, const QString& filePath);

private:
	static QVector<MsgEntry> g_messages;
	static QString           g_errorMessage;

	static std::unique_ptr<AppConfig> g_appConfig;   // RAII, évite fuite mémoire
};
