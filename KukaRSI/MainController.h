#pragma once
#include "WindowControllerBase.h"
#include "MainModel.h"
#include "MainWindow.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "Config.h"

class MainController : public WindowControllerBase
{
	Q_OBJECT
public:
	MainController(MainModel* model, MainWindow* view, QObject* parent = nullptr);
	~MainController();

private slots:
	void onViewCloseRequested() override;
	void onModelReleased();
	void onNavigationRequest(NavigationNode* newNode, NavigationNode* currentNode, bool* accept);
	void onNavigationDone(NavigationNode* node);

	void robotConfigSaved(const Config* config);

private:
	void setupTreeNodes();
	void setupConnections();
	void updateCentralWidget(NavigationNode* node);

	void navigateConfigurationNode();
	void navigateAppNode();

private:
	MainModel* m_model;
	MainWindow* m_view;
	Config* m_tempConfig;

	NavigationTree* m_tree;
	NavigationNode* m_rootNode;
	NavigationNode* m_configurationNode;
	NavigationNode* m_appNode;
};
