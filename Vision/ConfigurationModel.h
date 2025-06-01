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
	explicit ConfigurationModel(Config* srcConfig, QObject* parent = nullptr);

	Config* getEditableConfig() const;

public slots:
	void cancel();
	void reset();
	void save(const QString& path);
	void open(const QString& path);

private slots:
	void onConfigChanged(const ParameterBase* sender);

signals:
	void canceled();
	void changed();
	void saved(const Config* config);
	void opened(const QString& path);

private:
	Config* m_srcConfig;
	Config* m_editableConfig;
};
