#include "MainModel.h"
#include "AppStore.h"
#include "Camera.h"

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
	//AppStore::getCamera();

	ModelBase::release();
}
