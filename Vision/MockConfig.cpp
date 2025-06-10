#include "MockConfig.h"

MockConfig::MockConfig(QObject* parent) :
	Config(parent),
	m_param1("Param1", true, this),
	m_param2("Param2 long", 50, this),
	m_param3("Param3 hi", "Toto", StringParameter::Kind::Plain, this),
	m_param4("Param4", "Atat", StringParameter::Kind::FilePath, this),
	m_group1("Group1", this),
	m_param11("Param11", true, this),
	m_param12("Param12 long long", 50, this),
	m_param13("Param13 hi", "Toto", StringParameter::Kind::Plain, this),
	m_param14("Param14", "Atat", StringParameter::Kind::FilePath, this),
	m_group2("Group2", this),
	m_param21("Param21", true, this),
	m_param22("Param22 long", 50, this),
	m_param23("Param23 hi", "Toto", StringParameter::Kind::Plain, this),
	m_param24("Param24", "Atat", StringParameter::Kind::FilePath, this),
	m_group21("Group21", this),
	m_param211("Param211", true, this),
	m_param212("Param212 long", 50, this),
	m_param213("Param213 hi", "Toto", StringParameter::Kind::Plain, this)
{
	addParameters();
}

MockConfig::MockConfig(const MockConfig& config, QObject* parent) :
	Config(parent),
	m_param1("Param1", config.m_param1, this),
	m_param2("Param2 long", config.m_param2, this),
	m_param3("Param3 hi", config.m_param3, this),
	m_param4("Param4", config.m_param4, this),
	m_group1("Group1", this),
	m_param11("Param11", config.m_param11, this),
	m_param12("Param12 long long", config.m_param12, this),
	m_param13("Param13 hi", config.m_param13, this),
	m_param14("Param14", config.m_param14, this),
	m_group2("Group2", this),
	m_param21("Param21", config.m_param21, this),
	m_param22("Param22 long", config.m_param22, this),
	m_param23("Param23 hi", config.m_param23, this),
	m_param24("Param24", config.m_param24, this),
	m_group21("Group21", this),
	m_param211("Param211", config.m_param211, this),
	m_param212("Param212 long", config.m_param212, this),
	m_param213("Param213 hi", config.m_param213, this)
{
	m_param3.setKind(StringParameter::Kind::Plain);
	m_param4.setKind(StringParameter::Kind::FilePath);
	m_param13.setKind(StringParameter::Kind::Plain);
	m_param14.setKind(StringParameter::Kind::FilePath);
	m_param23.setKind(StringParameter::Kind::Plain);
	m_param24.setKind(StringParameter::Kind::FilePath);
	m_param213.setKind(StringParameter::Kind::Plain);

	addParameters();
}

void MockConfig::reset()
{
	MockConfig mockConfig;
	setFromConfig(&mockConfig, false);
}

Config* MockConfig::copy(QObject* parent) const
{
	MockConfig* newConfig = new MockConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

bool MockConfig::setFromConfig(const Config* src, bool copyPath)
{
	int numberOfParametersToSet = 15;
	int numberOfParametersSet = 0;

	Config::setFromConfig(src, copyPath);

	if (src)
	{
		if (BoolParameter* param = qobject_cast<BoolParameter*>(src->getParameter("Param1")))
		{
			m_param1.setValue(param->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* param = qobject_cast<NumericalParameter*>(src->getParameter("Param2 long")))
		{
			m_param2.setValue(param->getValue());
			numberOfParametersSet++;
		}
		if (StringParameter* param = qobject_cast<StringParameter*>(src->getParameter("Param3 hi")))
		{
			m_param3.setValue(param->getValue());
			numberOfParametersSet++;
		}	
		if (StringParameter* param = qobject_cast<StringParameter*>(src->getParameter("Param4")))
		{
			m_param4.setValue(param->getValue());
			numberOfParametersSet++;
		}

		if (GroupParameter* group = qobject_cast<GroupParameter*>(src->getParameter("Group1")))
		{
			if (BoolParameter* param = qobject_cast<BoolParameter*>(group->getParameter("Param11")))
			{
				m_param11.setValue(param->getValue());
				numberOfParametersSet++;
			}
			if (NumericalParameter* param = qobject_cast<NumericalParameter*>(group->getParameter("Param12 long long")))
			{
				m_param12.setValue(param->getValue());
				numberOfParametersSet++;
			}
			if (StringParameter* param = qobject_cast<StringParameter*>(group->getParameter("Param13 hi")))
			{
				m_param13.setValue(param->getValue());
				numberOfParametersSet++;
			}
			if (StringParameter* param = qobject_cast<StringParameter*>(group->getParameter("Param14")))
			{
				m_param14.setValue(param->getValue());
				numberOfParametersSet++;
			}
		}

		if (GroupParameter* group = qobject_cast<GroupParameter*>(src->getParameter("Group2")))
		{
			if (BoolParameter* param = qobject_cast<BoolParameter*>(group->getParameter("Param21")))
			{
				m_param21.setValue(param->getValue());
				numberOfParametersSet++;
			}
			if (NumericalParameter* param = qobject_cast<NumericalParameter*>(group->getParameter("Param22 long")))
			{
				m_param22.setValue(param->getValue());
				numberOfParametersSet++;
			}
			if (StringParameter* param = qobject_cast<StringParameter*>(group->getParameter("Param23 hi")))
			{
				m_param23.setValue(param->getValue());
				numberOfParametersSet++;
			}
			if (StringParameter* param = qobject_cast<StringParameter*>(group->getParameter("Param24")))
			{
				m_param24.setValue(param->getValue());
				numberOfParametersSet++;
			}

			if (GroupParameter* group21 = qobject_cast<GroupParameter*>(src->getParameter("Group21")))
			{
				if (BoolParameter* param = qobject_cast<BoolParameter*>(group21->getParameter("Param211")))
				{
					m_param211.setValue(param->getValue());
					numberOfParametersSet++;
				}
				if (NumericalParameter* param = qobject_cast<NumericalParameter*>(group21->getParameter("Param212 long")))
				{
					m_param212.setValue(param->getValue());
					numberOfParametersSet++;
				}
				if (StringParameter* param = qobject_cast<StringParameter*>(group21->getParameter("Param213 hi")))
				{
					m_param213.setValue(param->getValue());
					numberOfParametersSet++;
				}
			}
		}
	}

	return numberOfParametersSet == numberOfParametersToSet;
}

void MockConfig::addParameters()
{
	addParameter(&m_param1);
	addParameter(&m_param2);

	m_group1.addParameter(&m_param11);
	m_group1.addParameter(&m_param12);
	m_group1.addParameter(&m_param12);
	m_group1.addParameter(&m_param14);

	addParameter(&m_group1);

	addParameter(&m_param3);

	m_group2.addParameter(&m_param21);
	m_group2.addParameter(&m_param22);

	m_group21.addParameter(&m_param211);
	m_group21.addParameter(&m_param212);
	m_group21.addParameter(&m_param213);

	m_group2.addParameter(&m_group21);

	m_group2.addParameter(&m_param23);
	m_group2.addParameter(&m_param24);

	addParameter(&m_group2);

	addParameter(&m_param4);
}
