#include "MainModel.h"
#include "AppStore.h"

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
	ModelBase::release();
}
