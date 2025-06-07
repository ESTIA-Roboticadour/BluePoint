#pragma once
#include "WindowControllerBase.h"
#include "MainModel.h"
#include "MainWindow.h"
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
	void onNavigationRequest(NavigationNode* newNode, NavigationNode* currentNode, bool* accept);
	void onNavigationDone(NavigationNode* node);

private:
	void setupConnections();
	void updateCentralWidget(NavigationNode* node);

private:
	MainModel* m_model;
	MainWindow* m_view;
};
