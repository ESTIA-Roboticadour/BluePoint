#pragma once
#include "RobotConfig.h"

class AppStore
{
public:
	static void deleteAll();

	static void setIsInEdition(bool isInEdition);
	static bool isInEdition();

	static RobotConfig* getRobotConfig();
	static void setRobotConfig(RobotConfig* robotConfig);

private:
	static inline void deleteObject(QObject* o);

private:
	static bool s_isInEdition;

	static RobotConfig* s_robotConfig;
};
