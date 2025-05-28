#pragma once
#include "ParametersView.h"
#include "Config.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>

class ConfigurationView : public QWidget
{
	Q_OBJECT

public:
	explicit ConfigurationView(const QString& title, QWidget* parent = nullptr);

	void setConfig(const Config* config);

private:
	void buildUi(const QString& titleStr);

private slots:
	void onSaveButtonClicked();

signals:
	void cancelRequested();
	void resetRequested();
	void saveRequested(const QString& path);

private:
	QString m_configPath;
	ParametersView* m_parametersView{ nullptr };
	QPushButton* m_cancelButton{ nullptr };
	QPushButton* m_resetButton{ nullptr };
	QPushButton* m_saveButton{ nullptr };
};
