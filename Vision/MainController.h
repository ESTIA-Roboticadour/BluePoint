#pragma once
#include "WindowControllerBase.h"
#include "MainModel.h"
#include "MainWindow.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "ParameterBase.h"
#include "Config.h"
#include "MockConfig.h"

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

	void appConfigValidator(const ParameterBase* parameterChanged, Config* config);

	void appConfigPathChanged(const QString& path);
	void appConfigParameterChanged(const ParameterBase* sender);
	void appConfigSaved(const Config* config);
	void lightControlConfigSaved(const Config* config);
	void cameraConfigSaved(const Config* config);
	void roiConfigSaved(const Config* config);

private:
	void setupTreeNodes();
	void setupConnections();
	void updateCentralWidget(NavigationNode* node);

	void navigateDeviceNode();
	void navigateConfigurationNode();
	void navigateLightNode();
	void navigateCameraNode();
	void navigateRoiNode();

private:
	MainModel* m_model;
	MainWindow* m_view;
	Config* m_tempConfig;
	MockConfig m_mockConfig;

	NavigationTree* m_tree;
	NavigationNode* m_rootNode;
	NavigationNode* m_deviceNode;
	NavigationNode* m_configurationNode;
	NavigationNode* m_lightNode;
	NavigationNode* m_cameraNode;
	NavigationNode* m_roiNode;
	NavigationNode* m_appNode;
};
