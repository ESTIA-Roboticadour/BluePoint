#pragma once
#include "WindowControllerBase.h"
#include "MainModel.h"
#include "MainWindow.h"
#include "NavigationTree.h"
#include "NavigationNode.h"

class MainController : public WindowControllerBase
{
	Q_OBJECT
public:
	MainController(MainModel* model, MainWindow* view, QObject* parent = nullptr);
	~MainController();

private slots:
	void onViewCloseRequested() override;
	void onModelReleased();

private slots:
	void onNavigationDone(NavigationNode* node);

private:
	void setupTreeNodes();
	void setupConnections();
	void updateCentralWidget(NavigationNode* node);

private:
	MainModel* m_model;
	MainWindow* m_view;

	NavigationTree* m_tree;
	NavigationNode* m_rootNode;
	NavigationNode* m_deviceNode;
	NavigationNode* m_configurationNode;
	NavigationNode* m_workspaceNode;
	NavigationNode* m_roiNode;
	NavigationNode* m_appNode;
};
