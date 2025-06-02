#pragma once
#include "Config.h"
#include "StringParameter.h"
#include "ListParameterBase.h"
#include "ListParameter.h"
#include "GroupParameter.h"
#include "NumericalParameter.h"
#include "BoolParameter.h"

class MockConfig : public Config
{
	Q_OBJECT

public:
	explicit MockConfig(QObject* parent = nullptr);
	MockConfig(const MockConfig& config, QObject* parent = nullptr);
	~MockConfig() override = default;

	void reset() override;
	Config* copy(QObject* parent = nullptr) override;

private:
	bool setFromConfig(const Config* src, bool copyPath) override;

private:
	void addParameters();

private:
	BoolParameter m_param1;
	NumericalParameter m_param2;
	StringParameter m_param3;
	StringParameter m_param4;

	GroupParameter m_group1;
	BoolParameter m_param11;
	NumericalParameter m_param12;
	StringParameter m_param13;
	StringParameter m_param14;

	GroupParameter m_group2;
	BoolParameter m_param21;
	NumericalParameter m_param22;
	StringParameter m_param23;
	StringParameter m_param24;

	GroupParameter m_group21;
	BoolParameter m_param211;
	NumericalParameter m_param212;
	StringParameter m_param213;
};
