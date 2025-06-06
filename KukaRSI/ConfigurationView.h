#pragma once
#include "TransparentScrollArea.h"
#include "ParametersView.h"
#include "Config.h"

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>

class ConfigurationView : public TransparentScrollArea
{
	Q_OBJECT

public:
	ConfigurationView(const QString& title, bool isReadOnly = false, QWidget* parent = nullptr);

	void setConfig(const Config* config);

public slots:
	void onConfigModified();
	void onConfigCanceled();
	void onConfigSaved(const Config* config);

private slots:
	void onFullPathButtonClicked();
	void onSaveButtonClicked();
	void onOpenButtonClicked();

private:
	void buildUi(const QString& titleStr, bool isReadOnly);
	void updateUiConfig(bool isModified);
	void updateFileLabel();

signals:
	void cancelRequested();
	void resetRequested();
	void saveRequested(const QString& path);
	void openRequested(const QString& path);

private:
	QString m_configPath;
	bool m_isConfigModified;
	bool m_isFullPath;

	QLabel* m_pathLabel{ nullptr };
	QPushButton* m_fullPathButton{ nullptr };
	ParametersView* m_parametersView{ nullptr };
	QPushButton* m_cancelButton{ nullptr };
	QPushButton* m_resetButton{ nullptr };
	QPushButton* m_saveButton{ nullptr };
	QPushButton* m_openButton{ nullptr };
};
