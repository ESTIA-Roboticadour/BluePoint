#include "MainModel.h"

MainModel::MainModel(NavigationTree* tree, QObject* parent) :
	ModelBase(parent),
	m_tree(tree)
{
}

NavigationTree* MainModel::tree() const
{
	return m_tree;
}

void MainModel::release()
{
	// if camera open
	// close cam, wait signal to call ModelBase::release()
	// else
	ModelBase::release();
}
