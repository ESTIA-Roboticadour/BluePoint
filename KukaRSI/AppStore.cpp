#include "AppStore.h"
bool AppStore::s_isInEdition = false;
RobotConfig* AppStore::s_robotConfig = nullptr;

void AppStore::setIsInEdition(bool isInEdition) { s_isInEdition = isInEdition; }
bool AppStore::isInEdition() { return s_isInEdition; }

RobotConfig* AppStore::getRobotConfig()
{
	return s_robotConfig;
}

void AppStore::setRobotConfig(RobotConfig* robotConfig)
{
	if (!s_robotConfig)
	{
		s_robotConfig = (RobotConfig*)robotConfig->copy();
	}
}


void AppStore::deleteAll()
{
	deleteObject(s_robotConfig);
}

void AppStore::deleteObject(QObject* o)
{
	if (o)
	{
		o->deleteLater();
		o = nullptr;
	}
}
