#pragma once
#include "ModelBase.h"
#include "Config.h"
#include "ParameterBase.h"

#include <QObject>
#include <QString>

class ConfigurationModel : public ModelBase
{
	Q_OBJECT
public:
	explicit ConfigurationModel(const Config* config, QObject* parent = nullptr);

	const Config* getConfig() const;

	bool save(const QString& path) const;

private slots:
	void configChanged(const ParameterBase* sender);

private:
	const Config* m_srcConfig;
	Config* m_editableConfig;
};

