#pragma once
#include "ModelBase.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "Config.h"

#include <QObject>

class MainModel : public ModelBase
{
	Q_OBJECT
public:
	MainModel(NavigationTree* tree, QObject* parent = nullptr);
	~MainModel() override;

	QWidget* buildCentralWidget(const NavigationNode* node, QWidget* parent=nullptr);

	// getters
	NavigationTree* tree() const;

	// public
	void release() override;

private slots:
	void robotConfigSaved(const Config* config);

private:
	void setupTreeNodes();
	void tryOpenRobotConfig() const;

	QWidget* navigateConfigurationNode(QWidget* parent = nullptr);
	QWidget* navigateAppNode(QWidget* parent = nullptr);

private:
	NavigationTree* m_tree;
	NavigationNode* m_rootNode;
	NavigationNode* m_configurationNode;
	NavigationNode* m_appNode;

	Config* m_tempConfig;
};
