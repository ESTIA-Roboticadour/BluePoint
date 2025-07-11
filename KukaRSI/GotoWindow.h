#pragma once
#include "WindowBase.h"
#include "Config.h"
#include "ParametersView.h"

#include <QObject>

class GotoWindow : public WindowBase
{
	Q_OBJECT

public:
	explicit GotoWindow(QWidget* parent = nullptr);

	void setConfig(const Config* config);

private:
	void setupUI();

private:
	ParametersView* m_parametersView {nullptr};
};

