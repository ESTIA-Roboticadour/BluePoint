#pragma once
#include "ModelBase.h"
#include "NavigationTree.h"
#include "RobotKuka.h"

#include <QObject>

class MainModel : public ModelBase
{
	Q_OBJECT
public:
	MainModel(NavigationTree* tree, QObject* parent = nullptr);
	~MainModel() = default;

	// getters
	NavigationTree* tree() const;
	RobotKuka* getRobot() const;

	// public
	void release() override;

private:
	NavigationTree* m_tree;
	RobotKuka* m_robot;
};
