#include "MainModel.h"

MainModel::MainModel(NavigationTree* tree, QObject* parent) :
	ModelBase(parent),
	m_tree(tree),
	m_robot(new RobotKuka(this))
{
}

NavigationTree* MainModel::tree() const
{
	return m_tree;
}

RobotKuka* MainModel::getRobot() const
{
	return m_robot;
}

void MainModel::release()
{
	if (m_robot)
	{
		m_robot->stopMovement();
		m_robot->stop();
		m_robot->disconnectFromRobot();
	}
	ModelBase::release();
}
