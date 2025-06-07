#pragma once
#include "ModelBase.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "Config.h"
#include "MockConfig.h"
#include "ParameterBase.h"

#include <QObject>

class MainModel : public ModelBase
{
	Q_OBJECT
public:
	MainModel(NavigationTree* tree, QObject* parent = nullptr);
	~MainModel() override;

	// getters
	NavigationTree* tree() const;

	// public
	void release() override;
	QWidget* buildCentralWidget(const NavigationNode* node, QWidget* parent = nullptr);

private slots:
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

	QWidget* navigateDeviceNode(QWidget* parent=nullptr);
	QWidget* navigateConfigurationNode(QWidget* parent=nullptr);
	QWidget* navigateLightNode(QWidget* parent=nullptr);
	QWidget* navigateCameraNode(QWidget* parent=nullptr);
	QWidget* navigateRoiNode(QWidget* parent=nullptr);

signals:
	void warning(const QString& title, const QString& message);

private:
	NavigationTree* m_tree;
	NavigationNode* m_rootNode;
	NavigationNode* m_deviceNode;
	NavigationNode* m_configurationNode;
	NavigationNode* m_lightNode;
	NavigationNode* m_cameraNode;
	NavigationNode* m_roiNode;
	NavigationNode* m_appNode;

	Config* m_tempConfig;
	MockConfig m_mockConfig;
};
