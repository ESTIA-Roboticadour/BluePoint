#pragma once
#include "ModelBase.h"
#include "NavigationTree.h"

#include <QObject>

class MainModel : public ModelBase
{
	Q_OBJECT
public:
	MainModel(NavigationTree* tree, QObject* parent = nullptr);
	~MainModel() = default;

	// getters
	NavigationTree* tree() const;

	// public
	void release() override;

private:
	NavigationTree* m_tree;
};
