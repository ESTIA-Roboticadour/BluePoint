#pragma once
#include "RobotConfig.h"
#include <chrono>

class AppStore
{
public:
	static void deleteAll();

	static void setIsInEdition(bool isInEdition);
	static bool isInEdition();

	static RobotConfig* getRobotConfig();
	static void setRobotConfig(RobotConfig* robotConfig);

	static inline std::chrono::microseconds captureTime()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	}

	static inline void captureDataReceived()
	{ 
		m_dataReceivedUS = captureTime();
	}

	static inline long long dataReceived()
	{
		return m_dataReceivedUS.count();
	}

	static inline void captureDataReceivedEmitted()
	{
		m_dataReceivedEmittedUS = captureTime();
	}

	static inline long long dataReceivedEmitted()
	{
		return m_dataReceivedEmittedUS.count();
	}

	static inline void captureDataSendedUS()
	{
		m_dataSendedUS = captureTime();
	}

	static inline long long dataSended()
	{
		return m_dataSendedUS.count();
	}

	// Retourne le délai entre réception des données et émission du signal readyRead (ou équivalent)
	static inline long long delay_Received_to_Emitted()
	{
		return (m_dataReceivedEmittedUS - m_dataReceivedUS).count();
	}

	// Retourne le délai entre l’émission du signal et l’envoi des données (consigne)
	static inline long long delay_Emitted_to_Sended()
	{
		return (m_dataSendedUS - m_dataReceivedEmittedUS).count();
	}

	// Retourne le délai complet entre réception et envoi (boucle fermée)
	static inline long long delay_Sended_to_Received()
	{
		return (m_dataReceivedUS - m_dataSendedUS).count();
	}

	static inline void printTmpStr()
	{
		qDebug() << m_tmpStr;
		m_tmpStr.clear();
	}

	static inline void addToTmpStr(const QString& str)
	{
		m_tmpStr += str;
	}

private:
	static inline void deleteObject(QObject* o);

private:
	static bool s_isInEdition;

	static RobotConfig* s_robotConfig;

	static inline std::chrono::microseconds m_dataReceivedUS;
	static inline std::chrono::microseconds m_dataReceivedEmittedUS;
	static inline std::chrono::microseconds m_dataSendedUS;
	static inline QString m_tmpStr;
};
